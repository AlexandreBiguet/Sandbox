// Example program

#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Base {
  using Ptr = std::shared_ptr<Base>;
  Base(const std::string& n) : _n(n) {}
  virtual void hello() const { std::cout << "Hello base " << _n << "\n"; }
  std::string _n;
};

struct A : public Base {
  A(const std::string& n) : Base(n) {}
  void hello() const override { std::cout << "Hello A " << _n << "\n"; }
};

struct B : public Base {
  B(const std::string& n) : Base(n) {}
  void hello() const override { std::cout << "Hello B " << _n << "\n"; }
};

enum class Type { A, B };

template <typename T>
Base::Ptr create(Type type, const T& t) {
  if (type == Type::A) {
    return std::make_shared<A>(t);
  }
  return std::make_shared<B>(t);
}

int main() {
  Type type = Type::A;
  auto ptr = create(type, "coucou");
  ptr->hello();

  return 0;
}
