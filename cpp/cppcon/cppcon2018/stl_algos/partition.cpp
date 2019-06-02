#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

#include "utils.hpp"

int main() {

  std::vector<int> vec(10);
  std::iota(std::begin(vec), std::end(vec), 0);
  std::random_device device;
  std::mt19937 engine{device()};
  std::shuffle(std::begin(vec), std::end(vec), engine);

  std::cout << "Shuffled vector: \n";
  print(vec);

  auto pred = [](const auto &element) { return element < 5; };

  std::partition(std::begin(vec), std::end(vec), pred);

  std::cout << "Partionned vector: \n";
  print(vec);

  auto p_point = std::partition_point(std::begin(vec), std::end(vec), pred);

  std::cout << "Partion point : " << *p_point << "\n";

  std::cout << "Before partition point: \n";
  std::copy(std::begin(vec), p_point,
            std::ostream_iterator<int>(std::cout, " "));

  std::cout << "\nAfter partition point: \n";
  std::copy(p_point, std::end(vec), std::ostream_iterator<int>(std::cout, " "));

  std::cout << std::endl;

  return 0;
}