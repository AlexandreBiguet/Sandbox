//
//  Benchmark.hpp 
//  snmpp
//
//  Created on 22/10/2017 at 15:54.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * benchmark class that the user could
 * instantiate which allow to make a benchmark for a particular function.
 *  Implemented :
 *    - add a vector of tuple representing the different arguments the user
 *      wants to pass to his function to be benchmarked
 *    - add a number of time the function should be called with the same
 *      arguments in order to compute some statistical indicators (typically
 *      mean and variance). In the first implementation the benchmark tool
 *      will use its custom statistical. But the final implementation should
 *      use the snmpp statistical engine.
 *
 *   From sandbox/BenchmarkFinalDraft.cpp
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 *  TODO :  column formatted output
 ******************************************************************************/

#include <cmath>
#include <tuple>
#include <vector>

#include <boost/filesystem.hpp>

#include <snmpp/Utils/Sequence.hpp>
#include <snmpp/Utils/Tools.hpp>

#include "BenchmarkConfig.hpp"

namespace snmpp { namespace benchmark {

/**
 *
 * @tparam TimeUnit : Unit of time in which you want the result.
 *                    E.g std::chrono::nanoseconds
 *
 * @tparam Clock    : A clock with a static method ::now()
 *
 * @tparam Args     : The type of each argument that will be forward to the
 *                    function you want to benchmark
 */

template <
    typename TimeUnit,
    typename Clock,
    typename ...Args
>
class Benchmark {


    /***************************************************************************
     * Interface
     **************************************************************************/

  public:

    /**
     * Creation of a Benchmark object from a BenchmarkConfig
     **/
    explicit Benchmark( const BenchmarkConfig &config ) ;

    /**
     * Adding an item in the vector of arguments to be forward to the
     * function to be benchmarked
     * */
    void addArgs( const std::tuple< Args...> &t);

    /**
     * Execution of the benchmark using the callable object passed in argument
     * */
    template < typename Callable > void execute ( Callable func );




    /***************************************************************************
     * Private
     **************************************************************************/

  private:

    BenchmarkConfig _config;
    std::vector< std::tuple< Args ... >> _args;

    /**
     * Creation of the benchmark data directory, and writes the corresponding
     * config file
     *
     * return : a path to the benchmark data file
     * */
    boost::filesystem::path createDir ();

    /**
     * Compute the mean of a vector
     * -> Will be removed when snmpp has its Statistical Tools available
     * */
    double mean_impl( const std::vector < typename TimeUnit::rep > &v );

    /**
     * Compute the variance of a vector using it previously computed mean.
     * -> Will be removed when snmpp has its Statistical Tools available
     * */
    double var_impl
        ( const std::vector < typename TimeUnit::rep > &v, double mean );


    /**
     * The 'trick' consisting of calling measure_impl in measure function could
     * be useless if we use C++17 and std::apply( Callable &&f, Tuple &&t )
     *
     * -> We could consider implement in Utils an equivalent if we don't want
     * to go to 17 standard.
     *
     *  The SingleMeasure structure is nested private but it could be
     *  non-nested and used directly.
     *
     * */

    struct SingleMeasure {

        std::tuple<Args...> _tupleArgs;


        /**
         *  Construction of a SingleMeasure from a tuple
         *
         * Q : Should we pass by value and use std::move ?
         * */
        explicit SingleMeasure( const std::tuple<Args...> &t) : _tupleArgs(t){}

        /**
         * Measure the execution time of the Callable object passed in
         * argument.
         * */
        template< typename Callable >
        typename TimeUnit::rep measure( Callable func ) {

            return measure_impl
                (func, typename utils::SequenceGenerator<sizeof ...(Args)>::type());
        }

        /**
         * Measure implementation. The arguments needed by the function to be
         * benchmarked are saved in a tuple (_tupleArgs) which are forward to
         * the function using a sequence.
         * */
        template < typename Callable, std::size_t ... I>
        typename TimeUnit::rep measure_impl( Callable func, utils::Sequence<I...> ) {
            auto s = Clock::now();
            func( std::get<I>(_tupleArgs)...);
            auto e = Clock::now();
            auto duration = std::chrono::duration_cast<TimeUnit>(e-s);
            return duration.count();
        }

    };

};

/**
 * Constructor from config
 * */

template <typename T, typename C,typename ...Args>
Benchmark<T, C, Args...>::Benchmark(const BenchmarkConfig &config)
    : _config (config){}

/**
 * Adding an argument list
 * */

template <typename T, typename C,typename ...Args>
void Benchmark<T, C, Args...>::addArgs(const std::tuple<Args...> &t) {
    _args.push_back(t);
}

/**
 * Execute the benchmark
 * */

template <typename T, typename C,typename ...Args>
template <typename Callable>
void Benchmark<T,C,Args...>::execute( Callable func ){

    boost::filesystem::path data = createDir();

    boost::filesystem::ofstream ofs(data);

    ofs<<"# Function name : "<<_config.getFunctionName()<<"\n";
    ofs<<"# Statistical mean and variance calculated on a "
       <<_config.getIterationNumber()<<" sample \n";
     ofs<<"Time unit : "<<utils::getTimeUnit<T>()<<"\n#\n";
    ofs<<"# Bunch Nb     mean      sqrt(variance)  \n";

    std::size_t count(0);

    for( const auto &t : _args ){

        // TODO : print content of t

        ++count;
        std::vector<typename T::rep > results;
        const std::size_t iterNumber = _config.getIterationNumber();

        for ( std::size_t i = 0 ; i < iterNumber ; ++i ){
            SingleMeasure  m ( t );
            results.push_back( m.measure(func) );
        }

        double mean = mean_impl(results);
        double var = var_impl(results, mean);
        ofs<<count<<"\t"<<mean<<"\t"<<std::sqrt(var)<<"\n";
    }

    ofs.close();
}

/**
 * Calculation of mean
 * */

template <typename T, typename C,typename ...Args>
double Benchmark<T, C, Args...>::mean_impl
    ( const std::vector < typename T::rep > &v  ) {

    double mean(0.0);
    std::size_t c (0);

    for( const auto &i : v ){
        mean += static_cast<double>((i - mean)) / (c+1);
        ++c;
    }
    return mean;
}

/**
 * Calculation of the variance
 * */

template <typename T, typename C,typename ...Args>
double Benchmark<T, C, Args...>::var_impl
    (const std::vector<typename T::rep> &v, double mean) {

    double var(0.0);
    double d(0.0);
    std::size_t c (0);

    for( const auto &i : v ){
        d = static_cast<double>(i) - mean;
        var += (d*d - var) / (c+1);
        ++c;
    }

    return var;
}

/**
 * Creation of the benchmark data directory, and writes the corresponding
 * config file
 *
 * return : a path to the benchmark data file
 * */

template <typename T, typename C,typename ...Args>
boost::filesystem::path Benchmark<T, C, Args...>::createDir() {

    std::string dir_path = _config.getPathToBenchmarkDir();
    std::string date = utils::getCurrentDate();
    dir_path = utils::addTrailingSlash(dir_path);
    dir_path+= _config.getFunctionName() + '-' + date + '/';

    utils::createDirectory(dir_path);

    boost::filesystem::path conf_file ( dir_path + "config.txt" );

    boost::filesystem::ofstream ofs ( conf_file );

    ofs<<" Config file \n\n";
    ofs<<" Data : "<<date<<"\n";
    ofs<<" Function name : "<<_config.getFunctionName()<<"\n";
    ofs<<" List of parameter names : \n";
    auto param = _config.getArgumentNames();
    for( auto &i : param ){
        ofs<<"\t "<<i<<"\n";
    }
    ofs<<" Number different arguments to be passed  : "<<_args.size()<<"\n";
    ofs<<" Number of time each bunch of arg is used : "
       <<_config.getIterationNumber()<<"\n";

    ofs.close();

    return dir_path + "data.txt";
}

}} // namespace snmpp::benchmark

// Benchmark.hpp ends here