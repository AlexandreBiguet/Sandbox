/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   21-Jun-2018
 * @Filename: ostreamTemplateOverload.cpp
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 21-Jun-2018
 */

/**
 * Is it possible to overload the << operator with a generic object ?
 * -> Maybe it is possible but i don't know how to do it
 */

#include <iostream>
#include <ostream>
#include <string>

struct Sucks {
  virtual std::string toString() const = 0;
};

struct Toto : public Sucks {
  std::string _a;
  std::string _b;
  Toto() : _a("Hello,"), _b("World") {}
  std::string toString() const final { return _a + _b + '\n'; }
};

struct Tintin : public Sucks {
  std::string _a;
  std::string _b;
  Tintin() : _a("World, "), _b("Hello") {}
  std::string toString() const final { return _a + _b + '\n'; }
};

struct Tintin2 : public Sucks {
  double _a, _b;
  Tintin2() : _a(1.0), _b(2.0) {}
  std::string toString() const final {
    return std::to_string(_a) + ' ' + std::to_string(_b) + '\n';
  }
};

//
// mmmm.... Ok
//
// template <typename T>
// std::ostream& operator<<(std::ostream& os, const T& t) {
//   os << t.toString();
//   return os;
// }

std::ostream& operator<<(std::ostream& os, const Sucks& s) {
  os << s.toString();
  return os;
}

int main() {
  Toto toto;
  Tintin tintin;
  Tintin2 tintin2;

  std::cout << toto << tintin << std::endl;

  std::cout << toto;
  std::cout << tintin;

  std::cout << tintin2;
  return 0;
}
