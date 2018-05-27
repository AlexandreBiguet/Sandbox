//
//  main.cpp
//  Sandbox
//
//  Created by Alexandre Biguet on 17/05/2018 at 08:29.
//  Copyright © 2018 . All rights reserved.
//

#include <cstdlib>
#include <iostream>

#include <boost/dll/import.hpp>

#include "interface.hpp"

namespace Plugins = Sandbox::Plugins;

int main() {
  // Assuming the SandboxPlugins shared library is in MY_PLUGIN_PATH
  // Assuming MY_PLUGIN_PATH is not a ;-seperated list
  // Typically it should be a path like : $(install-dir)/ i.e. a path to
  // the place where the libSandboxPlugins (.dylib | .so) is installed

  auto pp = std::getenv("MY_PLUGIN_PATH");

  if (!pp) {
    std::cout << "MY_PLUGIN_PATH env. var should be defined \n";
    return -1;
  }

  boost::filesystem::path ldPath(pp);

  boost::shared_ptr<Plugins::Interface> plug1 =
      boost::dll::import<Plugins::Interface>(
          ldPath / "libSandboxPlugins", "toto_plugin1",
          boost::dll::load_mode::append_decorations);

  boost::shared_ptr<Plugins::Interface> plug2 =
      boost::dll::import<Plugins::Interface>(
          ldPath / "libSandboxPlugins", "toto_plugin2",
          boost::dll::load_mode::append_decorations);

  double x = 2.0;

  std::cout << "x   : " << plug1->calc(x) << "\n";
  std::cout << "x^2 : " << plug2->calc(x) << "\n";

  return 0;
}

// main.cpp ends here
