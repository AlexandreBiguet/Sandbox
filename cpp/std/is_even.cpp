/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   22 - Nov - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 22 - Nov - 2018
 */

#include <iostream>

constexpr bool is_even(size_t n) { return (n % 2) == 0; }

int main() {
  static_assert(true == is_even(2), "2 is even");
  static_assert(false == is_even(3), "3 is odd");
  // static_assert(true == is_even(3), "3 is odd");
  return 0;
}
