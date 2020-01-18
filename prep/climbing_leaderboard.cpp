//
//  climbing_leaderboard.cpp - interview_prep - Created by Alexandre BIGUET on 17/01/2020.
// --> https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem

#include "find_range.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

namespace {

template <typename Iter>
void print(Iter begin, Iter end) {
  auto it = begin;
  while (it != end) {
    std::cout << std::setw(3) << *it << " | ";
    ++it;
  }
}
void print_vector(const std::vector<int>& vec) { print(vec.begin(), vec.end()); }

std::vector<int> climbing_leaderboard(std::vector<int> scores, std::vector<int> alice) {
  auto nodup = std::unique(std::begin(scores), std::end(scores));
  print(std::begin(scores), nodup);
  std::cout << "\n\n";

  std::vector<int> results;
  results.reserve(alice.size());
  auto begin = std::begin(scores);
  auto end = nodup;

  for (const auto& alice_score : alice) {
    auto index = binary_find_range(begin, end, alice_score);
    std::cout << " [found index ] : " << index << "\n";

    int rank = index + 1;
    if (index > 0 && alice_score == scores[index - 1]) {
      rank = index;
    }

    results.push_back(rank);
  }

  return results;
}

}  // namespace

int main() {
  std::vector<int> scores{205, 150, 100, 100, 100, 80, 55, 50, 50, 45, 25, 20, 10, 10, 5};
  std::vector<int> alice{45};
  print_vector(scores);
  std::cout << "\n";
  print_vector(alice);
  std::cout << "\n";

  print_vector(climbing_leaderboard(scores, alice));

  std::cout << std::endl;

  return EXIT_SUCCESS;
}