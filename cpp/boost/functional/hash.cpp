/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   14 - Nov - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 14 - Nov - 2018
 */

#include <iostream>
#include <vector>

#include <boost/functional/hash.hpp>

// #define PRINT_STUFF

int main() {
  std::vector<double> vec{10.0, M_PI};
  std::vector<size_t> hash;

  const size_t Ntest = 10;
  hash.reserve(vec.size() * Ntest);

  boost::hash<double> hasher;

  for (size_t i = 0; i < Ntest; ++i) {
    for (const auto& e : vec) {
      hash.push_back(hasher(e));
    }
  }

#ifdef PRINT_STUFF
  for (const auto& e : vec) {
    std::cout << " [ " << e << " ]   ";
  }
  std::cout << '\n';

  for (const auto& e : hash) {
    std::cout << " [ " << e << " ]   ";
  }
  std::cout << '\n';
#endif

  for (size_t i = 0; i < vec.size(); ++i) {
    for (size_t j = i; j < hash.size(); j += vec.size()) {
      if (hash[i] != hash[j]) {
        std::cout << " -> not equal : [ " << i << " : " << hash[i] << "] and [ "
                  << j << " : " << hash[j] << "] \n";
        return -1;
      }
    }
  }

  std::cout << " --> all right \n";

  return 0;
}
