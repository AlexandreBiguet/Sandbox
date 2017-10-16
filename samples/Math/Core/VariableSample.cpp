//
//  VariableSample.cpp 
//  snmpp
//
//  Created on 16/10/2017 at 23:53.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#include <iostream>

#include <snmpp/Math/Core/Variable.hpp>

int main ( ) {

    snmpp::math::Variable<double> Var(snmpp::math::VariableType::Running);
    std::cout<<"Default construction (variable type) : "<<Var.toString()
             <<std::endl;

    snmpp::math::Variable<double>
        Var1(snmpp::math::VariableType::Running, 10.0);
    std::cout<<"construction with value (variable type) : "<<Var1.toString()
             <<std::endl;

    snmpp::math::Variable<double>
        Var2(snmpp::math::VariableType::Running, 1.0, -10.0, 10.0);
    std::cout<<"construction with value and interval(variable type) : "
             <<Var2.toString() <<std::endl;

    return 0;
}

// VariableSample.cpp ends here