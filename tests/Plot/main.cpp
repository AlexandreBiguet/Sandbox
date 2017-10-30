//
//  main.cpp 
//  snmpp
//
//  Created on 30/10/2017 at 01:17.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#include <cmath>
#include <iostream>

#include <snmpp/Math/Core/FuncBase.hpp>
#include <snmpp/Plot/Formatter.hpp>
#include <snmpp/Plot/GnuPlotter.hpp>

using namespace snmpp;

class SinFunc : public math::FuncBase {
  public:
    SinFunc(): math::FuncBase ( math::FuncBase::ConstructorInputType(
        {{"x", math::Variable(0., -5., 5., math::VariableType::Running)},
         {"a", math::Variable(0., -10., 10., math::VariableType::Parameter)},
         {"b", math::Variable(0., -10., 10., math::VariableType::Parameter)
         }}))
    {}

    void eval () override  {
        double x = _inputs.get("x").getValue();
        double a = _inputs.get("a").getValue();
        double b = _inputs.get("b").getValue();
        _outputs["f"] = a * std::sin( b*x );
    }
};

int main ( ){

    plot::Config config("plot-dir", "sin");
    config.useCurrentDateAsPrefix();

    SinFunc func;
    plot::GnuPlotter plotter(config,utils::FormattedOutput(15,6), func);

    plotter.addFixedValue("a", 10.0);
    plotter.addFixedValues("a", {1.0, 2.0, 3.0, 15.0, 13.0} );

    std::vector<double> fixed_b_vec({5.0, 12.0, 1.0});

    plotter.addFixedValues("b", fixed_b_vec);

    plotter.setFixedValuesNumber("x", 4);

    plotter.writeDataFiles();

    return 0;
}

// main.cpp ends here