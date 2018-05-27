//
//  templatedForLoop.cpp
//  Sandbox
//
//  Created by Alexandre Biguet on 25/04/2018 at 15:38.
//  Copyright © 2018 All rights reserved.
//

/**
 * test : inversed templated while loop
 */

#include <array>
#include <iostream>
#include <string>

template <size_t Dim, size_t N>
class Looper {
 public:
  static void loop(const std::array<double, Dim>& data) {
    std::cout << "[" << N << "] = " << data[N] << "\n";
    Looper<Dim, toBeContinued ? (N - 1) : 0>::loop(data);
  }

 private:
  enum { toBeContinued = (N - 1) != 0 };
};

template <size_t Dim>
class Looper<Dim, 0> {
 public:
  static void loop(const std::array<double, Dim>& data) {
    std::cout << "[0] = " << data[0] << "\n";
  }
};

int main() {
  std::array<double, 3> data{0.0, 1.0, 2.0};

  Looper<3, 2>::loop(data);

  return 0;
}

// templatedForLoop.cpp ends here
