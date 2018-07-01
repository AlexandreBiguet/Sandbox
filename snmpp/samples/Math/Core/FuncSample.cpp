//
//  FuncTest.cpp 
//  snmpp
//
//  Created on 21/10/2017 at 12:18.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>
#include <string>

#include <snmpp/Math/Core/FuncBase.hpp>

using namespace snmpp::math;

class LinFunc : public core::FuncBase<std::string,double> {

  public :

    LinFunc() : FuncBase(FuncBase::ConstructorInputType (        {{"x", core::Variable<double>(0., -5., 5., VariableType::Running)},
         {"a", core::Variable<double>(0., -10., 10., VariableType::Parameter)},
         {"b", core::Variable<double>(0., -10., 10., VariableType::Parameter)}}))
        {}


    void eval () override {

        double x = _inputs.get("x").getValue();
        double a = _inputs.get("a").getValue();
        double b = _inputs.get("b").getValue();

        double f1 = a*x + b;
        double f2 = b*x + a;

        _outputs["f1"] = f1;
        _outputs["f2"] = f2;
    }

};

int main () {

    LinFunc func;

    auto vals = func();

    std::cout<<"Calculating f1 and f2 with default values of variables : \n";
    for(const auto &i : vals) {
        std::cout<<i.first<<" = "<<i.second<<"\n";
    }

    std::cout<<"Calculating f1 and f2 with user-defined values  : \n";
    vals = func({{"a", 1.0},{"b", 2.0}, {"x", 3.0}});
    for(const auto &i : vals) {
        std::cout<<i.first<<" = "<<i.second<<"\n";
    }

    return 0;
}

// FuncTest.cpp ends here