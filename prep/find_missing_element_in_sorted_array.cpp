//
//  find_missing_element_in_sorted_array.cpp - interview_prep - Created by Alexandre BIGUET on 23/01/2020.
//

#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec{1, 3, 4, 5, 10, 13};

  std::vector<int> missing;

  for (int i = 0; i < vec.size() - 1; ++i) {
    int diff = vec[i + 1] - vec[i];

    if (diff == 1) {
      continue;
    }

    for (int j = vec[i]+1; j < vec[i] + diff; ++j) {
      missing.push_back(j);
    }
  }

  

  return 0;
}