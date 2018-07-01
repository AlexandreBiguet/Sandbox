//
//  main.cpp 
//  snmpp
//
//  Created on 23/10/2017 at 20:52.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

/*******************************************************************************
 * What I am wondering is :
 *   Is it more efficient to use
 *    -> the Utils/FormattedOutput tool
 *          or to use the
 *    -> boost::format tool
 ******************************************************************************/

#include <iostream>

#include <boost/format.hpp>

#include <snmpp/Benchmark/Benchmark.hpp>
#include <snmpp/Utils/FormattedOutput.hpp>

#include "../BenchmarkConfig.hpp"

void boostFormat (std::size_t N) {

    double a(15.0), b(2.0), c(-15.0), d(0.0);
    std::size_t i(12), n(1), m(10000);

    boost::format fmt("%-+15.6f %-+15.6f %-+15.6f %-+15.6f %-+15lu "
                           "%-+15lu %-+15lu");

    for(std::size_t j = 0 ; j < N ; ++j) {

        std::cout << fmt % a % b % c % d % i % n % m;
        std::cout << "\n";
    }
}

void formattedOutput(std::size_t N) {

    double a(15.0), b(2.0), c(-15.0), d(0.0);
    std::size_t i(12), n(1), m(10000);
    snmpp::utils::FormattedOutput col;

    for(std::size_t j = 0 ; j < N ; ++j) {

        std::cout<<col<<a<<col<<b<<col<<c<<col<<d;
        std::cout<<col<<i<<col<<n<<col<<m<<"\n";
    }
}

void printfFormat (std::size_t N) {

    double a(15.0), b(2.0), c(-15.0), d(0.0);
    std::size_t i(12), n(1), m(10000);

    boost::format fmt("%-+15.6f %-+15.6f %-+15.6f %-+15.6f %-+15lu "
                           "%-+15lu %-+15lu");

    for(std::size_t j = 0 ; j < N ; ++j) {

        printf("%-+15.6f %-+15.6f %-+15.6f %-+15.6f %-15lu "
                    "%-15lu %-15lu \n", a, b, c, d, i, n, m);
    }
}


using namespace snmpp::benchmark;
namespace chrono = std::chrono;


int main (){

    const std::string dir(SNMPP_BENCHMARK_DATA_DIR"/FormattedOutputs");

    {
        BenchmarkConfig config("boost-format", "N", 100, dir);

        Benchmark<chrono::microseconds, chrono::steady_clock, std::size_t>
            bench(config);

        bench.addArgs(std::make_tuple(10));
        bench.addArgs(std::make_tuple(100));
        bench.addArgs(std::make_tuple(1000));
        bench.addArgs(std::make_tuple(10000));

        bench.execute(&boostFormat);
    }

    {
        BenchmarkConfig config("snmmp-formatted-outputs", "N", 100, dir);

        Benchmark<chrono::microseconds, chrono::steady_clock, std::size_t>
            bench(config);

        bench.addArgs(std::make_tuple(10));
        bench.addArgs(std::make_tuple(100));
        bench.addArgs(std::make_tuple(1000));
        bench.addArgs(std::make_tuple(10000));

        bench.execute(&formattedOutput);
    }

    {
        BenchmarkConfig config("printfFormat", "N", 100, dir);

        Benchmark<chrono::microseconds, chrono::steady_clock, std::size_t>
            bench(config);

        bench.addArgs(std::make_tuple(10));
        bench.addArgs(std::make_tuple(100));
        bench.addArgs(std::make_tuple(1000));
        bench.addArgs(std::make_tuple(10000));

        bench.execute(&printfFormat);
    }

    return 0;
}


// main.cpp ends here