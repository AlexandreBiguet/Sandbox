#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define DEBUG_OUTPUT

#include "crush.hpp"
#include "interval.hpp"

// https://www.hackerrank.com/challenges/crush/problem

long arrayManipulation(int n, const std::vector<crush::Query>& queries) {
#ifdef DEBUG_OUTPUT
  std::cout << "n : " << n << std::endl;
#endif
  // return arrayManipulation_1(n, queries);
  return crush::arrayManipulation_3(n, queries);
}

void testing_interval();

int main() {
  // testing_interval();

  auto max = arrayManipulation(crush::test_case::array_size(), crush::test_case::queries());
  std::cout << "max element : " << max << std::endl;

  return 0;
}

void testing_interval() {
  crush::Interval i1(0, 4), i2(2, 3), i3(2, 6);
  std::cout << "i1 : ";
  print(i1);
  std::cout << "i2 : ";
  print(i2);
  std::cout << "i3 : ";
  print(i3);

  std::cout << "i1 \\cap i2 : ";
  print(crush::intersects(i1, i2));

  std::cout << "i1 \\cap i3 : ";
  print(crush::intersects(i1, i3));
}
