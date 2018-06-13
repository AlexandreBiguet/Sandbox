/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   13 - Jun - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#include <iostream>

void pretty(int a, int b) {
  std::cout << __PRETTY_FUNCTION__ << "a=" << a << "b=" << b << std::endl;
}

void function(int a) { std::cout << __FUNCTION__ << "a=" << a << std::endl; }

double func() {
  std::cout << __func__ << std::endl;
  return 1.0;
}

class Test {
 public:
  static void pretty(int a, int b) {
    std::cout << __PRETTY_FUNCTION__ << "a=" << a << "b=" << b << std::endl;
  }

  static void function(int a) {
    std::cout << __FUNCTION__ << "a=" << a << std::endl;
  }

  static double func() {
    std::cout << __func__ << std::endl;
    return 0.0;
  }
};

int main() {
  pretty(1, 2);
  function(10);
  func();

  Test::pretty(10, 20);
  Test::function(100);
  Test::func();

  return 0;
}
