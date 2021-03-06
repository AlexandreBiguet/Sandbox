/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   05 - Jul - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 06 - Jul - 2018
 */

#include "Stuff.hpp"

#include <iostream>

namespace myTest {

void hello(const std::string& name) {
  std::cout << "Hello " << name << std::endl;
}

double buggy(double* a) { return a[12345]; }

}  // namespace myTest
