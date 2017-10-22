//
//  Benchmark.cpp 
//  snmpp
//
//  Created on 21/10/2017 at 22:41.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

/**
 * Trying to implement a simple benchmark tool.
 *
 * Google benchmark is an option off course, but I am just having fun
 * https://github.com/google/benchmark
 *
 *
 * See also https://github.com/nickbruun/hayai
 * https://bruun.co/2012/02/07/easy-cpp-benchmarking
 */

#include <chrono>
#include <iostream>
#include <functional>
#include <random>
#include <tuple>
#include <utility>
#include <vector>

/**
 *
 * https://stackoverflow.com/questions/36612596/tuple-to-parameter-pack
 */

template <typename TimeUnit = std::chrono::nanoseconds>
struct TimeMeasure {

    template < typename T, typename ...Args >
    typename TimeUnit::rep measure( T func, Args&& ... args) {
        auto s = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto e = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<TimeUnit>(e-s);
        return duration.count();
    }

};


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

int main ( ){

    TimeMeasure<> t;
    auto time = t.measure(&function, 1000);
    std::cout<<"time = "<<time<<std::endl;
    return 0;
}

// Benchmark.cpp ends here