//
//  interface.hpp
//  Sandbox
//
//  Created by Alexandre Biguet on 17/05/2018 at 08:10.
//  Copyright © 2018 . All rights reserved.
//
#pragma once

#include <string>

namespace Sandbox {
namespace Plugins {

class Interface {
 public:
  virtual std::string name() const = 0;

  virtual double calc(double x) const = 0;

  virtual ~Interface() {}
};

}  // namespace Plugins
}  // namespace Sandbox

// interface.hpp ends here
