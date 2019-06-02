#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

int main() {
  std::vector<int> vec(10);
  std::iota(std::begin(vec), std::end(vec), 0);

  std::cout << "Input vector: \n";
  std::copy(std::begin(vec), std::end(vec),
            std::ostream_iterator(std::cout, " "));

  // std::rotate
  // std::shuffle
  // std::next_permutation
  // std::prev_permutation
  // std::reverse

  return 0;
}