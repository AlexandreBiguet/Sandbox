//
//  VariablesSample.cpp 
//  snmpp
//
//  Created on 17/10/2017 at 23:16.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>
#include <snmpp/Math/Core/Variables.hpp>

using namespace snmpp::math;

template <typename Key, typename ValueType>
void outputVar ( const core::Variables<Key, ValueType> &vars)
{
    for( const auto &it : vars ){
        std::string s( it.second.toString() );
        std::cout<<it.first<<" = "<<s<<std::endl;
    }
}


int main ( ){

    std::cout<<"Construction from a vector of tuple \n";

    std::vector<std::tuple<std::string,double, VariableType>>
        vec ({std::make_tuple("x", 1.0, VariableType::Running),
            std::make_tuple("y", 2.0, VariableType::Fixed)});
    core::Variables<std::string,double> Var(vec);

    std::cout<<"\nVariable constructed from vec of tuples : \n";
    outputVar(Var);


    std::cout<<"\nConstruction from a map of snmp::math variable object \n";

    std::map<std::string, core::Variable<double>> map(
        {{"x", core::Variable<double>(1.0, VariableType::Running)},
         {"y", core::Variable<double>(2.0, VariableType::Fixed)}}
    );

    core::Variables<std::string, double> Var2(map);

    std::cout<<"\nVariable constructed from map of variable objects : \n";
    outputVar(Var2);

    std::cout<<"\nadding a parameter 'param' :\n";
    Var2.add("param", core::Variable<double>(10.0, VariableType::Parameter));
    outputVar(Var2);

    std::cout<<" See src/Math/Core/Variables \n";


    return 0;
}

// VariablesSample.cpp ends here