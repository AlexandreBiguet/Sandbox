#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "interval.hpp"
#include "operation.hpp"

// https://www.hackerrank.com/challenges/crush/problem

#define DEBUG_OUTPUT

using Query = std::vector<int>;

std::vector<Query> queries() { return {{1, 5, 3}, {4, 8, 7}, {6, 9, 1}}; }
int array_size() { return 10; }

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

long arrayManipulation(int n, const std::vector<Query>& queries) {
#ifdef DEBUG_OUTPUT
  std::cout << "n : " << n << std::endl;
#endif
  // return arrayManipulation_1(n, queries);
  return arrayManipulation_2(n, queries);
}

void testing_interval();

int main() {
  // testing_interval();

  auto max = arrayManipulation(array_size(), queries());
  std::cout << "max element : " << max << std::endl;

  return 0;
}

void testing_interval() {
  crush::Interval i1(0, 4), i2(2, 3), i3(2, 6);
  std::cout << "i1 : ";
  print(i1);
  std::cout << "i2 : ";
  print(i2);
  std::cout << "i3 : ";
  print(i3);

  std::cout << "i1 \\cap i2 : ";
  print(crush::intersects(i1, i2));

  std::cout << "i1 \\cap i3 : ";
  print(crush::intersects(i1, i3));
}
