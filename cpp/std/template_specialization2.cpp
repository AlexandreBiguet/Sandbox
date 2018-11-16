/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   16 - Nov - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 16 - Nov - 2018
 */

#include <iostream>
#include <string>

template <typename T>
struct Base {
  Base(const T& t) : _t(t) {}
  const T& get() const { return T::toto; }
  T _t;
};

template <>
struct Base<double> {
  Base(const double& a) : _t(a) {}
  const double& get() const { return _t; }
  double _t;
};

template <>
struct Base<std::string> {
  Base(const std::string& a) : _t(a) {}
  const std::string& get() const {
    std::cout << "once \n";
    return _t;
  }
  std::string _t;
};

int main() {
  {
    Base<double> a1(1.0);
    std::cout << a1.get() << "\n";
  }

  {
    Base<std::string> a1("twice");
    std::cout << a1.get() << "\n";
  }

  {
    // Base<int> a1(1);
    // std::cout << a1.get() << "\n";
  }

  return 0;
}
