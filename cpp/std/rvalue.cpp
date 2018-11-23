/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   21-Nov-2018
 * @Filename: rvalue.cpp
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 21-Nov-2018
 */

#include <iostream>
#include <numeric>
#include <vector>

void func(const std::vector<int>& v) {
  std::cout << " const ref \n";
  for (const auto& e : v) {
    std::cout << e << " ";
  }
  std::cout << '\n';
}

void func(const std::vector<int>&& v) {
  std::cout << " rvalue \n";
  for (const auto& e : v) {
    std::cout << e << " ";
  }
  std::cout << '\n';
}

std::vector<int> create(size_t size = 2) {
  std::vector<int> v(size);
  std::iota(v.begin(), v.end(), 0);
  return v;
}

int main() {
  auto vec = create();
  func(vec);

  func(create(3));

  return 0;
}
