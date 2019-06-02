#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "utils.hpp"

std::vector<int> random_vector(std::size_t size, int min = 1, int max = 42) {
  std::vector<int> vec(size);

  std::random_device device;
  std::mt19937 engine{device()};
  std::uniform_int_distribution<int> dist{min, max};

  std::generate(std::begin(vec), std::end(vec),
                [&dist, &engine]() { return dist(engine); });

  return vec;
}

std::vector<int> shuffled_vector(std::size_t size) {
  std::vector<int> vec(size);
  std::iota(std::begin(vec), std::end(vec), 0);
  std::random_device device;
  std::mt19937 engine{device()};
  std::shuffle(std::begin(vec), std::end(vec), engine);
  return vec;
}

int main() {
  auto vec = shuffled_vector(20);

  std::cout << "Random vector: \n";
  print(vec);

  {
    auto v = vec;
    std::sort(std::begin(v), std::end(v));
    std::cout << "Sorted (with sort): \n";
    print(v);
  }

  {
    auto v = vec;
    std::partial_sort(std::begin(v), std::begin(v) + v.size() / 2, std::end(v));
    std::cout << "partial_sort (begin, size/2, end): \n";
    print(v);
  }

  {
    auto v = vec;
    std::nth_element(std::begin(v), std::begin(v) + 2, std::end(v));
    std::cout << "nth element (begin + 2) : \n";
    print(v);
  }

  {
    auto v = vec;
    std::make_heap(std::begin(v), std::end(v));
    std::sort_heap(std::begin(v), std::end(v));
    std::cout << "heap sort: \n";
    print(v);
  }

  {
    auto v = vec;
    std::sort(std::begin(v), std::begin(v) + v.size() / 2);
    std::sort(std::begin(v) + (v.size() / 2), std::end(v));
    std::inplace_merge(std::begin(v), std::begin(v) + v.size() / 2,
                       std::end(v));
    std::cout << "inplace merge: \n";
    print(v);
  }

  return 0;
}