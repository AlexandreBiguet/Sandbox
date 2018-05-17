//
//  plugs.hpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 17/05/2018 at 08:12.
//  Copyright © 2018 . All rights reserved.
//
#pragma once

#include "interface.hpp"

#include <memory>

#include <boost/config.hpp>

namespace Sandbox {
namespace myPlug {

class Plugin1 : public Plugins::Interface {
 public:
  Plugin1();

  std::string name() const override;

  double calc (double x) const override;

  ~Plugin1() override;

 private:
  std::string _name;
};

class Plugin2 : public Plugins::Interface {
 public:

  Plugin2();

  std::string name() const override;

  double calc(double x) const override;

  ~Plugin2() override;

 private:
  std::string _name;
};


}
} // namespace Sandbox 

// plugs.hpp ends here