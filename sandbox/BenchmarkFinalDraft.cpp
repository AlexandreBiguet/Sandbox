//
//  BenchmarkFinalDraft.cpp 
//  snmpp
//
//  Created on 22/10/2017 at 13:26.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

/**
 * This if the final draft for the simple benchmark tool that i would like to
 * implement in snmpp.
 *
 * What I want to do is to create a benchmark class that the user could
 * instantiate which allow to make a benchmark for a particular function.
 *  Needed :
 *    - add a vector of tuple representing the different arguments the user
 *      wants to pass to his function to be benchmarked
 *    - add a number of time the function should be called with the same
 *      arguments in order to compute some statistical indicators (typically
 *      mean and variance). In the first implementation the benchmark tool
 *      will use its custom statistical. But the final implementation should
 *      use the snmpp statistical engine.
 */


#include <chrono>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>


/**
 * For the moment I choose C++11 standard for which index_sequence is not
 * implemented. I don't want to use 14 standard just for that feature. So in
 * snmpp/Utils we will implemented a corresponding tool.
 *
 * If c++ 14 is needed elsewhere, we will go to 14
 * */

template <std::size_t ... >
struct Sequence {};

template <std::size_t N, std::size_t ...I>
struct SequenceGenerator : SequenceGenerator<N-1, N-1, I...>{};

template< std::size_t ...I>
struct SequenceGenerator<0, I...> {
    typedef Sequence<I...> type;
};

/**
 * In snmpp/Benchmark
 * */

struct BenchmarkConfig {

    // For statistical analysis
    std::size_t _numberOfIterations;

    // Where to put the result
    std::string _directoryName;
};

// std::chrono::steady_clock

template < typename TimeUnit, typename Clock, typename ...Args>
class Benchmark {

  private:
    BenchmarkConfig _config;
    std::vector< std::tuple< Args ... >> _args;

    /**
     * The 'trick' consisting of calling measure_impl in measure function could
     * be useless if we use C++17 and std::apply( Callable &&f, Tuple &&t )
     *
     * -> We could consider implement in Utils an equivalent if we don't want
     * to go to 17 standard.
     * 
     * */

    struct SingleMeasure {
        std::tuple<Args...> _tuple_args;

        /* Should we pass by value and use std::move ? */
        explicit SingleMeasure( const std::tuple<Args...> &t) : _tuple_args(t){}

        template< typename Callable >
        typename TimeUnit::rep measure( Callable func ) {

            return measure_impl
                (func, typename SequenceGenerator<sizeof ...(Args)>::type());
        }

        template < typename Callable, std::size_t ... I>
        typename TimeUnit::rep measure_impl( Callable func, Sequence<I...> ) {
            auto s = Clock::now();
            func( std::get<I>(_tuple_args)...);
            auto e = Clock::now();
            auto duration = std::chrono::duration_cast<TimeUnit>(e-s);
            return duration.count();
        }

    };



  public:
    explicit Benchmark( const BenchmarkConfig &config ) : _config(config){}

    void addArgs( const std::tuple< Args...> &t) {
        _args.push_back(t);
    }

    template < typename Callable >
    void execute ( Callable func ){

        std::size_t count(0);
        for( const auto &t : _args ){
            ++count;
            std::vector<typename TimeUnit::rep > results;

            for ( std::size_t i = 0 ; i < _config._numberOfIterations ; ++i ){
                SingleMeasure  m ( t );
                results.push_back( m.measure(func) );
            }
            double mean = mean_impl(results);
            std::cout<<"Arg List # "<<count<<" mean = "<<mean<<" \n";
        }


    }

  private:

    double mean_impl( const std::vector < typename TimeUnit::rep > &v ){
        typename TimeUnit::rep sum(0);
        for( auto &i : v ){
            sum+=i;
        }
        return static_cast<double>( sum / v.size() );
    }

};

/**
 * A simple test function
 *
 * */

void function( std::size_t N ){

    std::vector<double> vec;
    vec.reserve( N );
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 10.0);

    for (std::size_t n=0; n<N; ++n){
        vec.push_back(dis(gen));
    }

    std::sort( vec.begin(), vec.end() );
}

namespace chrono = std::chrono;

int main ( ){

    BenchmarkConfig config;
    config._numberOfIterations = 1000;


    Benchmark<chrono::microseconds, chrono::steady_clock, std::size_t>
        bench(config);

    bench.addArgs(std::make_tuple(10));
    bench.addArgs(std::make_tuple(100));
    bench.addArgs(std::make_tuple(1000));
    bench.addArgs(std::make_tuple(10000));

    bench.execute(&function);

    return 0;
}


// BenchmarkFinalDraft.cpp ends here