#pragma once

// C++ implementation below
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class Answer {
 public:
  static bool exists_simple(const std::vector<int> &tab, int k) {
    for (const auto &e : tab) {
      if (e == k) {
        return true;
      }
    }
    return false;
  }

  static bool exists(int ints[], int size, int k) {
    int ifirst(0), ilast(size);
    int imid;

    while (true) {
      int delta = ilast - ifirst;

      if (delta < 50) {
        std::vector<int> v;
        v.reserve(static_cast<size_t>(delta));

        for (int i = ifirst; i < ilast; ++i) {
          v.push_back(ints[i]);
        }

        return exists_simple(v, k);
      }

      imid = (ilast - ifirst) / 2;

      if (ints[imid] > k) {
        ilast = imid;
      } else if (ints[imid] < k) {
        ifirst = imid;
      } else {
        return true;
      }
    }
  }

  bool test(int *ints, int size, int k) {
    std::vector<int> arr;
    arr.reserve(size);
    for (int i = 0; i < size; ++i) {
      arr.push_back(ints[i]);
    }
    return std::find(std::begin(arr), std::end(arr), k) != std::end(arr);
  }

  static bool exist2(int ints[], int size, int k) {
    auto end = ints + size;
    return std::find(ints, end, k) != end;
  }

  static bool exists_2(int ints[], int size, int k) {
    auto end = ints + size;
    return std::binary_search(ints, end, k);
  }
};

// t1.cpp ends here
