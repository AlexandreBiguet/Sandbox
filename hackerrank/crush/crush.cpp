#include "crush.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>

#include "interval.hpp"
#include "operation.hpp"

#define DEBUG_OUTPUT

namespace crush {

// --------------------------------------------------------------------------------------------------------------------

// O(n * size(operation)) implementation
long arrayManipulation_1(int n, const std::vector<Query>& queries) {
  std::vector<long> v(n + 1, 0);
  for (const auto& query : queries) {
    auto first = std::next(std::begin(v), query[0]);
    auto last = std::next(std::begin(v), query[1] + 1);
    const auto& value = query[2];
    std::transform(first, last, first, [&value](const auto& elem) { return elem + value; });
#ifdef DEBUG_OUTPUT
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
#endif
  }
  return *std::max_element(std::next(std::begin(v)), std::end(v));
}

long arrayManipulation_1_bis(int n, const std::vector<Query>& queries) {
  std::vector<long> v(n + 1, 0);
  long max_val = std::numeric_limits<long>::min();

  for (const auto& query : queries) {
    auto first = std::next(std::begin(v), query[0]);
    auto last = std::next(std::begin(v), query[1] + 1);
    const auto& value = query[2];
    std::transform(first, last, first, [&value, &max_val](const auto& elem) {
      long tmp = elem + value;
      if (tmp > max_val) {
        max_val = tmp;
      }
      return tmp;
    });
#ifdef DEBUG_OUTPUT
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
#endif
  }
  return max_val;
}

// --------------------------------------------------------------------------------------------------------------------

long arrayManipulation_2(int n, const std::vector<Query>& queries) {
  std::vector<crush::Operation> operations;
  operations.reserve(queries.size());
  std::for_each(std::begin(queries), std::end(queries),
                [&operations](const auto& query) { operations.emplace_back(crush::Operation(query)); });

#ifdef DEBUG_OUTPUT
  print(operations);
#endif

  long maxsum = std::numeric_limits<long>::min();

  for (int value = 1; value <= n; ++value) {
    auto next = find_if(std::begin(operations), std::end(operations),
                        [&value](const auto& o) { return crush::within(o, value); });
    long sum = 0;
    while (next != std::end(operations)) {
      sum += next->_value;
      next =
          find_if(std::next(next), std::end(operations), [&value](const auto& o) { return crush::within(o, value); });
    }
    if (sum > maxsum) {
      maxsum = sum;
    }
  }

  return maxsum;
}

namespace test_case {
std::vector<Query> queries() { return {{1, 5, 3}, {4, 8, 7}, {6, 9, 1}}; }
int array_size() { return 10; }
}  // namespace test_case

long arrayManipulation_3(int n, const std::vector<Query>& queries) {
  std::vector<long> v(n + 1, 0);
  for (const auto& query : queries) {
    v[query[0]] += query[2];
    if (query[1] + 1 < n + 1) {
      v[query[1] + 1] -= query[2];
    }
  }

#ifdef DEBUG_OUTPUT
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<long>(std::cout, " "));
  std::cout << std::endl;
#endif

  long max = std::numeric_limits<long>::min();
  long sum = 0;
  for (const auto& e : v) {
    sum += e;
    if (sum > max) {
      max = sum;
    }
  }
  return max;
}

}  // namespace crush
