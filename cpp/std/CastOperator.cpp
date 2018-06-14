/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   14 - Jun - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 14 - Jun - 2018
 */

/**
 * Understand how the cast operators work
 * -> conversion operator cannot take parameters
 * -> Why should we use a conversion operator and not constructor ?
 *
 * Food for thought :
 *  - use conversion method when there is no possibility to add a new
 * constructor (e.g class A is defined in a third party library)
 *  - use conversion method to convert to primitive types (but I don't really
 * see another use case than the bool operator)
 *  - use constructor when possible (cyclic dependencies)
 *  - use explicit constructor and conversion method (except for the bool
 * operator)
 */

#include <cmath>
#include <iostream>
#include <string>

class B;

class A {
 public:
  explicit A(const std::string& a) : _a(a) {}
  explicit A(const B& b);  // implementation should be after B class Definition
  explicit A(B&& b);
  const std::string& get() const { return _a; }

 private:
  std::string _a;
};

class C {
 public:
  explicit C(int n) : _n(n) {}
  C(const B& b);
  int get() const { return _n; }

 private:
  int _n;
};

class B {
 public:
  explicit B(double b) : _b(b) {}
  double get() const { return _b; }

  // explicit const conversion member function to an A
  explicit operator A() const {
    std::cout << "B class : call to conversion to an A object \n";
    return A{std::to_string(_b)};
  }

  // impliciti non-const conversion member function to a C
  operator C() {
    std::cout << "B class : call to conversion to a C object \n";
    return C{static_cast<int>(std::ceil(_b))};
  }

 private:
  double _b;
};

A::A(const B& b) : _a(std::to_string(b.get())) {
  std::cout << "Construction of an A from a const B& \n";
}

A::A(B&& b) : _a(std::to_string(b.get())) {
  std::cout << "Construction of an A from a B (rvalue) \n";
}

C::C(const B& b) : _n(static_cast<int>(std::ceil(b.get()))) {
  std::cout << "Construction of a C from a B (const ref) \n";
}

int main() {
  B b(12.0);
  std::cout << "Value of b : " << b.get() << "\n";

  auto a = static_cast<A>(b);
  std::cout << "Value of b converted to a A object : " << a.get() << "\n\n";

  A a2(b);
  std::cout << "Value of b converted to a A object : " << a2.get() << "\n\n";

  A a3(B{10.0});
  std::cout << "Value of b converted to a A object : " << a3.get() << "\n\n";

  C c = b;
  std::cout << "Value of b converted to a C object: " << c.get() << "\n\n";

  C c2(b);
  std::cout << "Value of b converted to a C object: " << c2.get() << "\n\n";

  return 0;
}
