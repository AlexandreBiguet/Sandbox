// Example program

#include <iostream>
#include <numeric>
#include <vector>

int main() {
  std::vector<int> integers(10);
  std::iota(integers.begin(), integers.end(), 1);

  std::vector<std::reference_wrapper<const int>> refs;

  for (const auto& i : integers) {
    refs.push_back(i);
  }

  for (const auto& r : refs) {
    std::cout << r << "";
  }

  std::cout << std::endl;

  return 0;
}
