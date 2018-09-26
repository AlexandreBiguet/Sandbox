//
//  inheritance.cpp
//  Sandbox
//
//  Created by Alexandre Biguet on 16/05/2018 at 13:54.
//  Copyright © 2018 . All rights reserved.
//

/**
 * Testing inheritance using boost::any
 */

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <boost/any.hpp>

enum class Type { Undefined, First, Second, Third, Fourth };

static std::map<Type, std::string> type_str{/* NOLINT */
                                            {Type::Undefined, "Undefined Type"},
                                            {Type::First, "First Type"},
                                            {Type::Second, "Second Type"},
                                            {Type::Third, "Third Type"}};

std::string toString(Type type) { return type_str[type]; }

namespace Simple {

class TotoBase {

public:
  TotoBase(Type type, size_t id) : _type(type), _id(id) {}

  explicit TotoBase(size_t id) : TotoBase(Type::Undefined, id) {}

  size_t id() const { return _id; }
  Type type() const { return _type; }

private:
  Type _type;
  size_t _id;
};

class Toto1 : public TotoBase {

public:
  Toto1(size_t id, double a) : TotoBase(Type::First, id), _a(a) {}
  double a() const { return _a; }

public:
  double _a;
};

class Toto2 : public TotoBase {

public:
  Toto2(size_t id, size_t s) : TotoBase(Type::Second, id), _s(s) {}

  size_t s() const { return _s; }

private:
  size_t _s;
};

} // namespace Simple

namespace Real {

class Base {

public:
  std::size_t id() const { return _id; }

  Type type() const { return _type; }

  virtual boost::any get() const = 0;

  virtual ~Base() = default;

protected:
  Base(Type type, std::size_t id) : _type(type), _id(id) {}

private:
  Type _type;
  std::size_t _id;
};

class Daughter1 : public Base {

public:
  Daughter1(std::size_t id, double a) : Base(Type::First, id), _a(a) {}

  boost::any get() const override { return boost::any(_a); }

private:
  double _a;
};

class Daughter2 : public Base {

public:
  Daughter2(std::size_t id, size_t z) : Base(Type::Second, id), _z(z) {}

  boost::any get() const override { return _z; }

private:
  std::size_t _z;
};

class Daughter3 : public Base {
public:
  Daughter3(std::size_t id, std::vector<int> &&list)
      : Base(Type::Third, id), _list(list) {}

  boost::any get() const override { return _list; }

private:
  std::vector<int> _list;
};

struct Data {
  Data(double a, double b) : _a(a), _b(b) {}
  double _a, _b;
  std::string toString() const {
    return std::to_string(_a) + " " + std::to_string(_b);
  }
};

class Daughter4 : public Base {
public:
  Daughter4(std::size_t id, const Data &data)
      : Base(Type::Fourth, id), _data(data) {}

  boost::any get() const override { return _data; }

private:
  Data _data;
};

} // namespace Real

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

void simple();
void real();

int main() {

  simple();

  real();

  return 0;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

void real() {
  std::vector<std::unique_ptr<Real::Base>> list;
  list.emplace_back(std::make_unique<Real::Daughter1>(2, 120.0));
  list.emplace_back(std::make_unique<Real::Daughter1>(5, 1.0));
  list.emplace_back(std::make_unique<Real::Daughter2>(1, 100));
  list.emplace_back(std::make_unique<Real::Daughter2>(12, 10));
  list.emplace_back(
      std::make_unique<Real::Daughter3>(3, std::vector<int>{1, 2, 3}));
  list.emplace_back(
      std::make_unique<Real::Daughter4>(12, Real::Data(10.0, 12.0)));

  for (const auto &elem : list) {
    if (elem->type() == Type::First) {
      std::cout << "id " << elem->id() << " "
                << boost::any_cast<double>(elem->get()) << " \n";
    } else if (elem->type() == Type::Second) {
      std::cout << "id " << elem->id() << " "
                << boost::any_cast<std::size_t>(elem->get()) << " \n";
    } else if (elem->type() == Type::Third) {
      std::cout << "id " << elem->id() << " ";
      auto list = boost::any_cast<std::vector<int>>(elem->get());
      for (const auto &l : list) {
        std::cout << l << " ";
      }
    } else {
      std::cout << "id " << elem->id() << " ";
      std::cout << boost::any_cast<Real::Data>(elem->get()).toString() << "\n";
    }
    std::cout << std::endl;
  }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

void simple() {

  std::vector<Simple::TotoBase> totos;

  totos.emplace_back(Simple::TotoBase(0));
  totos.emplace_back(Simple::Toto1(2, 3));
  totos.emplace_back(Simple::Toto2(1, 2));

  for (const auto &toto : totos) {
    std::cout << toto.id() << " " << toString(toto.type()) << "\n";
  }
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// inheritance.cpp ends here
