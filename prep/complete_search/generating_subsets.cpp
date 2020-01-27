//
//  generating_subsets.cpp - interview_prep - Created by Alexandre BIGUET on 25/01/2020.
//  -> Generating all subsets of a set
//  sum_{i=0}^N C_i^N = 2^N

#include <cstdlib>
#include <iostream>
#include <vector>

namespace {

void print_subset_recursive(const std::vector<int>& input, int k, std::vector<int>& subset) {
  if (k == input.size()) {
    if (subset.empty()){
      std::cout << "{empty set}";
    }
    for (const auto& e : subset) {
      std::cout << e << " ";
    }
    std::cout << std::endl;
    return;
  }

  print_subset_recursive(input, k + 1, subset);
  subset.push_back(k);
  print_subset_recursive(input, k + 1, subset);
  subset.pop_back();
}

void print_subset_bit(const std::vector<int>& input) {
  for(int i = 0; i < (1<<input.size()); ++i) {
    for(size_t j = 0 ; j < input.size(); ++j) {
      if (i & (1<<j)) {
        std::cout << input[j] << " ";
      }
    }
    std::cout << std::endl;
  }
}

}  // namespace

int main() {
  std::vector<int> subset;
  print_subset_recursive({0, 1, 2}, 0, subset);

  std::cout << std::endl << std::endl;

  print_subset_bit({0, 1, 3});

  return EXIT_SUCCESS;
}
