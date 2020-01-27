//
//  generating_permutations.cpp - interview_prep - Created by Alexandre BIGUET on 25/01/2020.
//

#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

namespace {

template <typename Func>
void recursive_permutation_internal(Func func, std::vector<bool>& chosen, std::vector<size_t>& permutation,
                                    size_t size);

template <typename Func>
void recursive_permutation(Func func, size_t size) {
  std::vector<bool> chosen(size, false);
  std::vector<size_t> permutation;
  recursive_permutation_internal(func, chosen, permutation, size);
}

template <typename Func>
void recursive_permutation_internal(Func func, std::vector<bool>& chosen, std::vector<size_t>& permutation,
                                    size_t size) {
  if (permutation.size() == size) {
    func(permutation);
    return;
  }

  for (size_t i = 0; i < size; ++i) {
    if (chosen[i]) {
      continue;
    }

    chosen[i] = true;
    permutation.push_back(i);
    recursive_permutation_internal(func, chosen, permutation, size);
    chosen[i] = false;
    permutation.pop_back();
  }
}

template <typename Func>
void iterative_permutation (Func func, size_t size) {

  std::vector<size_t> permutation(size, 0);
  std::iota(std::begin(permutation), std::end(permutation), 0);

  do {
    func(permutation);
  } while(std::next_permutation(std::begin(permutation), std::end(permutation)));

}

}  // namespace

int main() {

  recursive_permutation([](const std::vector<size_t>& permutation){
    for(const auto& e : permutation) {
      std::cout << e << " ";
    }
    std::cout << std::endl;
  }, 3);

  std::cout << std::endl << std::endl;

  iterative_permutation([](const std::vector<size_t>& permutation){
    for(const auto& e : permutation) {
      std::cout << e << " ";
    }
    std::cout << std::endl;
  }, 3);

  return EXIT_SUCCESS;
}
