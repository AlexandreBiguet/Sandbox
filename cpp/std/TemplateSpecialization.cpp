/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   15 - Jun - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 15 - Jun - 2018
 */
#include <array>
#include <iostream>

template <std::size_t Dim, typename T>
struct Test {
  Test() = default;
  Test(double a, double b) : _data{{a, b}} {}

  std::array<T, Dim> _data;
};

template <std::size_t Dim, typename T>
void print(const Test<Dim, T>& test);

template <typename T>
void print(const Test<2, T>& test) {
  std::cout << std::get<0>(test._data) << " " << std::get<1>(test._data)
            << "\n";
}

int main() {
  Test<2, double> test(1.0, 2.0);
  std::get<1>(test._data) = 0.0;
  print(test);
  return 0;
}
