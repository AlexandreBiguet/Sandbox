#pragma once

class Algorithm {
 public:
  /** @return the position of the dancer at stage
   * n​​​​​​​‌‌​​‌​‌​​​‌​​‌​‌‌​​​‌‌‌‌
   */
  static int getPositionAt(int n) {
    // 0 : 0
    // 1 : +1
    // 2 : -2
    // n : (n-1)-(n-2)

    // iterative or recursive ?

    // iterative O(n)

    // buffer overflow

    int r = n % 6;

    if (r == 0) {
      return 0;
    } else if (r == 1) {
      return 1;
    } else if (r == 2) {
      return -2;
    }

    int i(1);
    int j(-2);
    int temp;
    int pos(-1);
    for (int k = 2; k < n; ++k) {
      temp = j - i;
      i = j;
      j = temp;
      pos += j;
    }
    return pos;
  }
};
