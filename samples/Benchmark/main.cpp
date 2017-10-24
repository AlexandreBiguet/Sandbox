//
//  main.cpp 
//  snmpp
//
//  Created on 22/10/2017 at 17:13.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>
#include <vector>
#include <random>


#include <snmpp/Benchmark/Benchmark.hpp>


void function( std::size_t N, double a __attribute__((unused))){

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


using namespace snmpp::benchmark;
namespace chrono = std::chrono;

int main ( ){

    std::vector<std::string> argnames({"N", "a"});
    BenchmarkConfig config("test-function",argnames, 100, "data" );

    Benchmark<chrono::microseconds,
              chrono::steady_clock,
              std::size_t, double> bench(config);

    bench.addArgs(std::make_tuple(10   , 1.0));
    bench.addArgs(std::make_tuple(100  , 2.0));
    bench.addArgs(std::make_tuple(1000 , 3.0));
    bench.addArgs(std::make_tuple(10000, 4.0));

    bench.execute(&function);

    return 0;
}

// main.cpp ends here