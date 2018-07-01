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

using namespace snmpp::math;

int main () {

    core::Variable<double> Var(VariableType::Running);
    std::cout<<"Default construction (variable type) : "<<Var.toString()
             <<std::endl;

    core::Variable<double>
        Var1(10.0, VariableType::Running);
    std::cout<<"construction with value (variable type) : "<<Var1.toString()
             <<std::endl;

    core::Variable<double>
        Var2(1.0, -10.0, 10.0, VariableType::Running);
    std::cout<<"construction with value and interval(variable type) : "
             <<Var2.toString() <<std::endl;

    Var2.setType(VariableType::Parameter);
    auto type = Var2.getType();
    std::cout<<"new type : "<< static_cast<int>(type)
             <<" -> "<<Var2.typeToString() <<std::endl;

    std::cout<<"value stay the same : "<<Var2.getValue()<<std::endl;
    std::cout<<" and interval "<<Var2.getLower()<<","
             <<Var2.getUpper() <<std::endl;

    //std::cout<<""

    return 0;
}

// VariableSample.cpp ends here