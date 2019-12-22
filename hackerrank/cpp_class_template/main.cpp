#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

/*Write the class AddElements here*/

template <typename T>
struct AddElements {
  explicit AddElements(const T& t) : _t(t) {}
  T add(const T& t) const { return _t + t; }
  T _t;
};

constexpr std::size_t g_max_size = 100;

template <>
struct AddElements<std::string> {
  explicit AddElements(const std::string& str) : _len (str.size()) {
    std::copy(std::make_move_iterator(std::begin(str)), std::make_move_iterator(std::end(str)), std::begin(_char_array));
  }

  std::string concatenate(const std::string& str) {
    std::copy(std::make_move_iterator(std::begin(str)), std::make_move_iterator(std::end(str)), std::begin(_char_array) + _len);
    return {_char_array.data()};
  }

  std::size_t _len;
  std::array<char, g_max_size> _char_array{0};

};

int main() {
  int n, i;
  cin >> n;
  for (i = 0; i < n; i++) {
    string type;
    cin >> type;
    if (type == "float") {
      double element1, element2;
      cin >> element1 >> element2;
      AddElements<double> myfloat(element1);
      cout << myfloat.add(element2) << endl;
    } else if (type == "int") {
      int element1, element2;
      cin >> element1 >> element2;
      AddElements<int> myint(element1);
      cout << myint.add(element2) << endl;
    } else if (type == "string") {
      string element1, element2;
      cin >> element1 >> element2;
      AddElements<string> mystring(element1);
      cout << mystring.concatenate(element2) << endl;
    }
  }
  return 0;
}
