//
//  RangeFinder.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 04/09/2018 at 12:21.
//

/// Using the previous sort by index trick, the aim is to find the lower and
/// upper bound of input value
/// Example :
/// v = [0, 1, 2, 3, ..., 9]
/// x = 2.5
/// lower = 2
/// upper = 3
/// because x \in [ v[lower] v[upper] ]

/// using dichotomy no-brain like method.
/// Returns the two indexes lower and upper
/// Corner cases:
/// * If input value is equal to v[i] then output range is [i-1 ; i+1].
/// * If input is v.front output range is [0, 1]
/// * If input is v.back output range is [n-2 , n-1]
/// (where n is nb of elem in v)

#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include <boost/format.hpp>

/// \brief checkout what is written above
/// \tparam T
/// \param v
/// \param value
/// \return
template <typename T>
std::pair <std::size_t, std::size_t>
get_range_sorted(const std::vector<T>& v, const T& value) {

  std::size_t ilow{0};
  std::size_t ihig{v.size() - 1};

  std::size_t imid = (ilow + ihig) / 2;

  while((ihig - ilow) > 1) {
    if (value < v[imid]) {
      ihig = imid;
    }

    if (value > v[imid]) {
      ilow = imid;
    }

    if (value == v[imid]) {
      break;
    }

    imid = (ilow + ihig) / 2;
  }

  return {ilow, ihig};

}

/// \brief See Sandbox/cpp/sort_by_index/main.cpp file
/// \tparam T
/// \param vec
/// \return
template <typename T>
static std::vector<std::size_t> get_sorted_indexes(const std::vector<T>& vec) {
  std::vector<std::size_t> indexes;
  indexes.resize(vec.size());
  std::iota(indexes.begin(), indexes.end(), 0);
  std::sort(indexes.begin(), indexes.end(), [&vec](size_t i1, size_t i2) {
    return (vec[i1] < vec[i2]);
  });
  return indexes;
}

/// \brief same as above with sorted_indexes so that :
/// v'[i] = v[sorted_indexes[i]] is sorted in ascinding order
/// \tparam T
/// \param v
/// \param sorted_indexes
/// \param value
/// \return
template <typename T>
std::pair <std::size_t, std::size_t>
get_range(const std::vector<T>& v,
    const std::vector<std::size_t>& sorted_indexes, double value) {

  std::size_t ilow{0};
  std::size_t ihig{v.size() - 1};

  std::size_t imid = (ilow + ihig) / 2;

  while((ihig - ilow) > 1) {
    if (value < v[sorted_indexes[imid]]) {
      ihig = imid;
    }

    if (value > v[sorted_indexes[imid]]) {
      ilow = imid;
    }

    if (value == v[sorted_indexes[imid]]) {
      break;
    }

    imid = (ilow + ihig) / 2;
  }

  return {ilow, ihig};
}

int main(int argc, char** argv) {

  double value(2.5);

  if (argc > 1) {
    value = std::stod(argv[1]);
  }

  std::vector <double> v;
  v.resize(10);
  std::iota(v.begin(), v.end(), 0);

  std::cout << "\nInput vector : \n";
  std::for_each(v.begin(), v.end(), [](const double &a) {
    std::cout << boost::format("%6.2f") % a;
  });
  std::cout << '\n';

  std::cout << "input value : " << value << "\n";

  if (!( (value <= v.back()) && (value >= v.front()))) {
    std::cout << "input value should be contained in [0 ; 9] \n";
    return -1;
  }

  auto p = get_range_sorted(v, value);
  auto ilow = p.first;
  auto ihig = p.second;

  if (ihig - ilow > 1) {
    std::cout << "Input value appears to be equal to value at index \n";
  }

  std::cout << boost::format(
      "%6.2f is in { %6.2f ; %6.2f} with indexes {%2d : %2d} \n")
      % value % v[ilow] % v[ihig] % ilow % ihig ;

  std::cout << "\n\n shuffling input vector : \n";

  std::random_device rd;
  std::mt19937 rangen(rd());

  std::shuffle(v.begin(), v.end(), rangen);

  std::cout << "\nInput vector (shuffled): \n";
  std::for_each(v.begin(), v.end(), [](const double &a) {
    std::cout << boost::format("%6.2f") % a;
  });
  std::cout << '\n';

  auto sorted_indexes = get_sorted_indexes(v);

  std::cout << "\nRe-ordered vector : \n";
  std::for_each(sorted_indexes.begin(), sorted_indexes.end(), [&v](std::size_t idx) {
    std::cout << boost::format("%6.2f") % v[idx];
  });
  std::cout << '\n';

  p = get_range(v, sorted_indexes, value);
  ilow = p.first;
  ihig = p.second;

  if (ihig - ilow > 1) {
    std::cout << "Input value appears to be equal to value at index \n";
  }

  std::cout << boost::format(
      "\n%6.2f is in { %6.2f ; %6.2f} with indexes {%2d : %2d} \n")
      % value % v[sorted_indexes[ilow]] % v[sorted_indexes[ihig]] % ilow % ihig ;


  return 0;
}


// RangeFinder.cpp ends here