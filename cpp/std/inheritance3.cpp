//
//  inheritance3.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 27/09/2018 at 15:02.
//
#include <iostream>
#include <memory>
#include <utility>

template <typename T>
class Base : public T {
 public:
  using Type = T;
  using Ptr = std::shared_ptr<Base>;
  ~Base() = default;

  template <typename ...Args>
  Base(Args&& ... args) : T(std::forward<Args...>(args...)) { }

  virtual const T& get() const = 0;
};

template <typename T>
class Tone {
 public:
  Tone(const T& t) : _t(t) { }
  void set(const T& t) { _t = t; }
  T t() const { return _t; }
 private:
  T _t;
};

template <typename T>
class Son1 : public Base <Tone<T>> {
 public:
  Son1(const T& t) : Base <Tone<T>> (t) { }
  const Tone<T>& get() const override { return *this; }

 private:

};

int main() {

  Son1<int> son1(1);
  auto t = son1.get();
  std::cout << "value : " << t.t() << '\n';
  son1.set(2);
  t = son1.get();
  std::cout << "value : " << t.t() << '\n';

  return 0;
}

// inheritance3.cpp ends here
