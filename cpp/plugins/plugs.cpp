//
//  plugs.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 17/05/2018 at 08:19.
//  Copyright © 2018 . All rights reserved.
//

#include "plugs.hpp"

#include <iostream>

#include <boost/dll/alias.hpp>

namespace Sandbox {
namespace myPlug {

// ----------------------------------------------------------------------------
Plugin1::Plugin1() : _name("Plugin1") { }

// ----------------------------------------------------------------------------

std::string Plugin1::name() const {
  return _name;
}

// ----------------------------------------------------------------------------

double Plugin1::calc(double x) const {
  return x;
}

// ----------------------------------------------------------------------------

Plugin1::~Plugin1() {
  std::cout << "plugin 1 destruction \n";
}

// ----------------------------------------------------------------------------

Plugin2::Plugin2() : _name ("Plugin2") {

}

// ----------------------------------------------------------------------------

std::string Plugin2::name() const {
  return _name;
}

// ----------------------------------------------------------------------------

double Plugin2::calc(double x) const {
  return x*x;
}

// ----------------------------------------------------------------------------

Plugin2::~Plugin2() {
  std::cout << "plugin 2 destruction \n";
}

// ----------------------------------------------------------------------------

extern "C" BOOST_SYMBOL_EXPORT Plugin1 toto_plugin1;
Plugin1 toto_plugin1; /* NOLINT */

extern "C" BOOST_SYMBOL_EXPORT Plugin2 toto_plugin2;
Plugin2 toto_plugin2; /* NOLINT */


}
}

// plugs.cpp ends here