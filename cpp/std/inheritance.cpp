//
//  inheritance.cpp
//  Sandbox
//
//  Created by Alexandre Biguet on 16/05/2018 at 13:54.
//  Copyright © 2018 . All rights reserved.
//

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>

enum class Type { Undefined, First, Second };

static std::map < Type, std::string > type_str{
    {Type::Undefined, "Undefined Type"},
    {Type::First, "First Type"},
    {Type::Second, "Second Type"}};

std::string toString(Type type) {
  return type_str[type];
}

class TotoBase {

 public:

  TotoBase(Type type, size_t id) : _type(type), _id(id) { }

  explicit TotoBase(size_t id) : TotoBase(Type::Undefined, id) { }

  size_t id() const { return _id; }
  Type type() const { return _type; }

 private:

  struct Impl;

  Type _type;
  size_t _id;

};


class Toto1 : public TotoBase {

 public:

  Toto1(size_t id, double a) : TotoBase(Type::First, id), _a(a) { }
  double a() const { return _a; }

 public:
  double _a;

};

class Toto2 : public TotoBase {

 public:

  Toto2(size_t id, size_t s) : TotoBase(Type::Second, id), _s(s) { }

  size_t s() const { return _s; }

 private:
  size_t _s;

};

int main () {

  std::vector<TotoBase> totos;

  totos.emplace_back(TotoBase(0));
  totos.emplace_back(Toto1(2, 3));
  totos.emplace_back(Toto2(1, 2));

  for (const auto& toto : totos) {
    std::cout << toto.id() << " " << toString(toto.type()) << "\n";
  }

  return 0;
}


// implptr.cpp ends here