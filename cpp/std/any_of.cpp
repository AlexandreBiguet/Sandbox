#include <algorithm>
#include <array>
#include <iostream>

/// \return true if any element of a1 is greater than corresponding element in
/// a2
static bool cmp(const std::array<int, 3>& a1, const std::array<int, 3>& a2) {
  size_t count{0};
  return std::any_of(std::begin(a1), std::end(a1), [&count, &a2](auto& elem) {
    bool val = elem > a2[count];
    ++count;
    return val;
  });
}

int main() {
  std::array<int, 3> arr{1, 2, 3};
  std::array<int, 3> tab{0, 1, 2};

  bool problem(false);

  if (cmp(tab, arr)) {
    problem = true;
  }

  if (!cmp(arr, tab)) {
    problem = true;
  }

  std::cout << (problem ? "problem" : "ok");
  std::cout << '\n';

  return 0;
}
