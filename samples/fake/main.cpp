//
//  main.cpp.cpp 
//  snmpp
//
//  Created on 15/10/2017 at 22:29.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>

//#include <snmpp/fake/fake.hpp>
#include "fake.hpp"

int main ( ){

    double x = snmpp::fake::fake(10.0);
    std::cout<<x<<std::endl;

    std::cout<<"Current date : "<<snmpp::fake::getCurrentDate()<<std::endl;

    return 0;
}

// main.cpp.cpp ends here