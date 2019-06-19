#pragma once

#include <vector>

namespace crush {

using Query = std::vector<int>;

namespace test_case {
std::vector<Query> queries();
int array_size();
}  // namespace test_case

// Slow implementations
long arrayManipulation_1(int n, const std::vector<Query>& queries);
long arrayManipulation_1_bis(int n, const std::vector<Query>& queries);
long arrayManipulation_2(int n, const std::vector<Query>& queries);

// O(n) implementation
long arrayManipulation_3(int n, const std::vector<Query>& queries);
}  // namespace crush
