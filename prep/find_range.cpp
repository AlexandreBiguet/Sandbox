//
//  find_range.cpp - interview_prep - Created by Alexandre BIGUET on 16/01/2020.
//

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "find_range.hpp"

namespace {

template <typename Iter>
void helper(Iter begin, Iter end, int val) {
  auto index = binary_find_range(begin, end, val);
  std::cout << "[index : " << index << " ] --> ";
  auto it = begin;
  while (it != end) {
    if (index == std::distance(begin, it)) {
      std::cout << "[" << val << "] ";
    }
    std::cout << *it << " ";
    ++it;
  }

  if (index > std::distance(begin, --end)) {
    std::cout << "[" << val << "] ";
  }

  std::cout << std::endl;
}

}  // namespace

int main() {
  std::vector<int> values{210, 205, 190, 100, 99, 80, 70, 65, 30};
  for (const auto& v : values) {
    std::cout << std::setw(3) << v << " ";
  }
  std::cout << std::endl;
  for (size_t i = 0; i < values.size(); ++i) {
    std::cout << std::setw(3) << i << " ";
  }

  std::cout << "\n\n";

  helper(std::begin(values), std::end(values), 105);
  helper(std::begin(values), std::end(values), 220);
  helper(std::begin(values), std::end(values), -5);
  helper(std::begin(values), std::end(values), 80);
  helper(std::begin(values), std::end(values), 210);
  helper(std::begin(values), std::end(values), 30);

  return EXIT_SUCCESS;
}
