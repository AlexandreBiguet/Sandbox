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
 * A possible way to convert tuple to parameter pack in C++11
 * In C++14 we could use std::index_sequence
 *
 * https://stackoverflow.com/questions/36612596/tuple-to-parameter-pack
 */

template <typename TimeUnit = std::chrono::nanoseconds>
struct TimeMeasure {

    template < typename T, typename ...Args >
    typename TimeUnit::rep measure(T func, Args&& ... args) {
        auto s = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto e = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<TimeUnit>(e-s);
        return duration.count();
    }

};

template <std::size_t ... >
struct Sequence {};

template <std::size_t N, std::size_t ...I>
struct SequenceGenerator : SequenceGenerator<N-1, N-1, I...>{};

template< std::size_t ...I>
struct SequenceGenerator<0, I...> {
    typedef Sequence<I...> type;
};

template < typename TimeUnit, typename ...Args>
struct SingleMeasure {
    std::tuple<Args...> _args;

    /* Should we pass by value and use std::move ? */
    explicit SingleMeasure(const std::tuple<Args...> &t) : _args(t){}

    template< typename Callable >
    typename TimeUnit::rep measure(Callable func) {

        return measure_impl
            (func, typename SequenceGenerator<sizeof ...(Args)>::type());
    }

    template < typename Callable, std::size_t ... I>
    typename TimeUnit::rep measure_impl(Callable func, Sequence<I...>) {
        auto s = std::chrono::steady_clock::now();
        func(std::get<I>(_args)...);
        auto e = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<TimeUnit>(e-s);
        return duration.count();
    }

};

void function(std::size_t N) {

    std::vector<double> vec;
    vec.reserve(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 10.0);

    for (std::size_t n=0; n<N; ++n){
        vec.push_back(dis(gen));
    }

    std::sort(vec.begin(), vec.end());
}

template< typename TimeUnit >
double mean(const std::vector< typename TimeUnit::rep > &v){
    typename TimeUnit::rep sum(0);
    for(auto &i : v) {
        sum+=i;
    }
    return static_cast<double>(sum / v.size());
}

int main (){

    using TimeUnit = std::chrono::microseconds;

    std::size_t N = 10000;
    std::size_t Niter = 1000;
    std::vector<TimeUnit::rep> t1, t2;
    t1.reserve(Niter);
    t2.reserve(Niter);

    for(std::size_t i = 0 ; i < Niter ; ++i) {

        TimeMeasure<TimeUnit> t;
        t1.push_back(t.measure(&function, N));
        //std::cout << "time = " << time << std::endl;

        std::tuple<std::size_t> tuple = std::make_tuple(N);
        SingleMeasure<TimeUnit, std::size_t> m(tuple);
        t2.push_back(m.measure(&function));
        //std::cout << "time = " << time << std::endl;
    }

    std::cout<<" mean 1 : "<<mean<TimeUnit>(t1)<<std::endl;
    std::cout<<" mean 2 : "<<mean<TimeUnit>(t2)<<std::endl;

    return 0;
}

// Benchmark.cpp ends here