//
//  GenericCaller.cpp 
//  snmpp
//
//  Created on 21/10/2017 at 19:46.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <functional>
#include <iostream>

/**
 * The aim of these tests if to understand how a class (named Caller here)
 * can take anything callable as argument and the arguments needed by the
 * callable and forward them to it.
 *
 * No problem to do this.
 * -> A manip is needed when a member-function is given to the Caller
 *    see code.
 * */

double func ( double x ){
    std::cout<<" func \n";
    return 2.0*x;
}

struct Test {
    double arg = 2.0;
    double func ( double x ){
        std::cout<<" Test func \n";
        return arg * x;
    }
    static void test ( double x, int n ){
        std::cout<<" Test test : "<<n*x<<"\n";
    }
};

struct Caller {

    template< typename T, typename ...Args >
    static void call ( T f, Args&& ... args ){
        f( std::forward<Args>(args)...);
    }

};

int main ( ){

    Caller::call( &func, 10.0 );

    Caller::call( &Test::test, 5.0, 1 );

    Test tobj;
    Caller::call( std::bind( &Test::func, tobj, std::placeholders::_1), 10.0 );

    auto fct = [](double a, double b,const std::string &s ){
        std::cout<<s<<" = "<<a+b<<std::endl;
    };

    Caller::call( fct, 1.0, 2.0, "fct");

    Caller::call( [](const std::string &s) {
        std::cout<<"Hello, "<< s ;
    }, "World");

    return 0;
}


// GenericCaller.cpp ends here