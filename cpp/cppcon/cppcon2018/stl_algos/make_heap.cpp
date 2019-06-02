#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "utils.hpp"

int main() {
  std::vector<int> vec(10);
  std::iota(std::begin(vec), std::end(vec), 0);

  std::cout << "Initial vector: \n";
  print(vec);

  std::make_heap(std::begin(vec), std::end(vec));

  std::cout << "Heapified vector: \n";
  print(vec);

  std::cout << "Pushing back element to vector: \n";
  vec.push_back(12);

  std::push_heap(std::begin(vec), std::end(vec));

  std::cout << "Using push_heap:\n";
  print(vec);

  std::cout << "Removing the max element of previous vector: \n";

  std::pop_heap(std::begin(vec), std::end(vec));
  vec.pop_back();
  print(vec);

  std::cout << "Sorting the vector by consecutive call of pop_heap: \n";

  {
    std::size_t count(0);
    while (count != vec.size()) {
      std::pop_heap(std::begin(vec), std::end(vec) - count);
      ++count;
    }
    print(vec);
  }

  return 0;
}