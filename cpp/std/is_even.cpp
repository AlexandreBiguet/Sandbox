/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   22 - Nov - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 22 - Nov - 2018
 */

#include <iostream>

constexpr bool is_even(size_t n) { return (n % 2) == 0; }

constexpr bool is_larger(size_t n, size_t bound) { return (n > bound); }

template <size_t N>
void func() {
  static_assert((is_even(N) == true) && (is_larger(N, 4)),
                "N must be even and larger than 4");
  std::cout << N << std::endl;
}

int main() {
  static_assert(true == is_even(2), "2 is even");
  static_assert(false == is_even(3), "3 is odd");
  // static_assert(true == is_even(3), "3 is odd");
  // func<2>();
  // func<5>();
  func<6>();
  return 0;
}
