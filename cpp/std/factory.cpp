// Example program

#include <iostream>
#include <memory>
#include <string>
#include <utility>
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

struct C : public Base {
  C(const std::string& str, double a) : Base(str), _a(a) {}
  void hello() const override {
    std::cout << "Hello C " << _n << " [" << _a << "]\n";
  }
  double _a;
};

enum class Type { A, B, C };

// template <typename T>
// Base::Ptr create(Type type, const T& t) {
//   if (type == Type::A) {
//     return std::make_shared<A>(t);
//   }
//   return std::make_shared<B>(t);
// }

// possible to construct
template <typename T, typename... Args>
std::enable_if_t<std::is_constructible<T, Args...>::value, std::shared_ptr<T> >
create(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

// impossible to construct
template <typename T, typename... Args>
std::enable_if_t<!std::is_constructible<T, Args...>::value, std::shared_ptr<T> >
create(Args&&...) {
  return nullptr;
}

template <class... Args>
Base::Ptr create(Type type, Args&&... args) {
  switch (type) {
    case Type::A:
      return create<A>(std::forward<Args>(args)...);
    case Type::B:
      return create<B>(std::forward<Args>(args)...);
    case Type::C:
      return create<C>(std::forward<Args>(args)...);
  }
}

int main() {
  Type type = Type::A;
  auto ptr = create(type, "coucou");
  ptr->hello();
  ptr = create(Type::B, "mmm");
  ptr->hello();

  ptr = create(Type::A, std::string("coucouco"));
  ptr->hello();

  ptr = create(Type::C, std::string("coucouco"), 12.0);
  ptr->hello();

  return 0;
}
