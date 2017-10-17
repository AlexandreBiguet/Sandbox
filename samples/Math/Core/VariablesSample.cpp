//
//  VariablesSample.cpp 
//  snmpp
//
//  Created on 17/10/2017 at 23:16.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <snmpp/Math/Core/Variables.hpp>

namespace sm = snmpp::math;

int main () {

    std::vector<std::tuple<std::string,sm::VariableType, double>>
                m ({std::make_tuple("x",sm::VariableType::Running, 1.0),
                    std::make_tuple("y", sm::VariableType::Fixed, 2.0)});
    snmpp::math::Variables<std::string,double> Var(m);

    return 0;
}


// VariablesSample.cpp ends here