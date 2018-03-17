//
//  QuantitySample.cpp 
//  snmpp
//
//  Created on 16/10/2017 at 22:07.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#include <iostream>

#include <snmpp/Math/Core/Quantity.hpp>

using namespace snmpp::math;

int main (){

    core::Quantity<double> Qd;
    std::cout<<"Default constructor : "<<Qd.toString()<<std::endl;

    double val(10.0);
    Qd.setValue(val);
    std::cout<<"value set to 10.0 : "<<Qd.toString()<<std::endl;
    std::cout<<"get value should be 10.0 : "<<Qd.getValue()<<std::endl;

    auto interval = Qd.getInterval();
    std::cout<<"get Interval returned : low:"<<interval.lower()<<" "
        "upp:"<<interval.upper()<<std::endl;

    double low(-10.0), upp(10.0);
    Qd.setUpper(upp);
    std::cout<<"setUpper to 10.0 : "<<Qd.toString()<<" upper : "
             <<Qd.getUpper()<<std::endl;

    Qd.setLower(low);
    std::cout<<"setLower to 10.0 : "<<Qd.toString()<<" lower : "
             <<Qd.getLower()<<std::endl;


    core::Quantity<double> Q1(4.0);
    std::cout<<"Construction with value "<<Q1.toString()<<std::endl;

    core::Quantity<double> Q2(4.0, -1.0, 10.0);
    std::cout<<"Construction with value and interval "
             <<Q2.toString()<<std::endl;

    Q2.setInterval(-10.0, 1.0);
    std::cout<<"setInterval to -10; 1 : "<<Q2.toString()<<std::endl;
    return 0;
}

// QuantitySample.cpp ends here