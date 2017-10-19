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

using VarType = snmpp::math::VariableType ;

int main ( ) {

    snmpp::math::Variable<double> Var(VarType::Running);
    std::cout<<"Default construction (variable type) : "<<Var.toString()
             <<std::endl;

    snmpp::math::Variable<double>
        Var1(10.0, VarType::Running);
    std::cout<<"construction with value (variable type) : "<<Var1.toString()
             <<std::endl;

    snmpp::math::Variable<double>
        Var2(1.0, -10.0, 10.0, VarType::Running);
    std::cout<<"construction with value and interval(variable type) : "
             <<Var2.toString() <<std::endl;

    Var2.setType(VarType::Parameter);
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