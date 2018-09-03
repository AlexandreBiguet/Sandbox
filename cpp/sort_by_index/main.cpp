//
//  main.cpp
//  Sandbox
//
//  Created by Alexandre Biguet on 03/09/2018 at 09:57.
//

/// Create a random list of integer [list]
/// construct a list of index [indexes] so that list[indexes] is sorted
/// Prints to stdout [ shuffled values ] [indexes] [shuffled values(indexes)]

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int main() {
  const std::size_t nval(100);

  std::vector<int> values;
  std::vector<int> indexes;

  values.resize(nval);
  indexes.resize(values.size());

  std::iota(values.begin(), values.end(), 0);

  std::random_device rd;
  std::mt19937 rangen(rd());

  std::shuffle(values.begin(), values.end(), rangen);

  std::iota(indexes.begin(), indexes.end(), 0);

  std::sort(indexes.begin(), indexes.end(),
            [&values](std::size_t i1, std::size_t i2) {
              return values[i1] < values[i2];
            });

  auto count{0};
  std::for_each(indexes.begin(), indexes.end(), [&count, &values](size_t idx) {
    std::cout << values[count] << "\t\t" << idx << "\t\t" << values[idx]
              << "\n";
    ++count;
  });

  return 0;
}

// main.cpp ends here
