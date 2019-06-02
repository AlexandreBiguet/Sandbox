#pragma once

#include <iostream>
#include <vector>

template <template <typename, typename> typename V, typename T>
void print(const V<T, std::allocator<T>> &v) {
  for (const auto &e : v) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}
