//
//  find_range.hpp - interview_prep - Created by Alexandre BIGUET on 17/01/2020.
//

#include <algorithm>
#include <iterator>

template <typename Iter>
std::size_t binary_find_range(Iter begin, Iter end, int val) {
  // element in [begin, end] are assumed to be sorted in descending order
  // returns the index val should have if inserted in [begin, end] so that descending ordering is kept

  std::pair<Iter, Iter> range;
  range.first = begin;
  range.second = --end;

  if (val >= *range.first) {
    return 0;
  } else if (val <= *range.second) {
    return std::distance(begin, end) + 1;
  }

  while (true) {
    auto mid = std::distance(range.first, range.second) / 2;
    auto mid_it = std::next(range.first, mid);

    if (val > *mid_it) {
      range.second = mid_it;
    } else {
      range.first = mid_it;
    }

    if (*range.first == val) {
      return std::distance(begin, range.first);
    }

    if (*range.second == val) {
      return std::distance(begin, range.second);
    }

    if (std::distance(range.first, range.second) == 1) {
      return std::distance(begin, range.second);
    }
  }
}

