/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   24 - Jun - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 05 - Jul - 2018
 */

#include "Cool.hpp"

#include <iostream>
#include <map>

static std::map<int, std::string> mapConversion{
    {0, "Good"}, {1, "Morning"}, {2, "Vietnam"}};

namespace myTest {

std::string getString(int a) {
  if (a <= 2 && a >= 0) {
    return mapConversion[a];
  }
  return std::string("Nothing");
}

void anotherFunction() { std::cout << std::endl; }

}  // namespace myTest
