//
//  Demo2.cpp
//  project
//
//  Created by Alexandre BIGUET on 26/05/2018.
//

#include <iostream>
#include "Demo.hpp"

namespace project {
namespace Demo {
namespace bonjour {

static double aVeryLongFunctionNameWithALotOfParameters(int first, int second,
                                                        int third) {
  std::cout << "this is a very super long string that should be splitted into "
               "several pieces"
            << std::endl;
  return (double)(first + second + third);
}

void demo2() { std::cout << " Demo 2 \n"; }

}  // namespace bonjour
}  // namespace Demo
}  // namespace project
