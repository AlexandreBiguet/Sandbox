//
//  conversion.cpp
//  Sandbox
//
//  Created by Alexandre Biguet on 23/05/2018 at 13:09.
//

/// Testing conversion operator overload (explicit or not ?)

#include <iostream>

namespace Test {

class Point {

 public:
  Point(double x, double y) : _x(y), _y(y) { }
  double x() const { return _x; }
  double y() const { return _y; }

 private:

  double _x;
  double _y;
};

class Toto {
 public:
  Toto(double x, double y) : _x(y), _y(y) { }
  double x() const { return _x; }
  double y() const { return _y; }

 private:

  double _x;
  double _y;
};

class Coord {
 public:
  Coord(double x, double y) : _x(x), _y(y) { }
  double x() const { return _x; }
  double y() const { return _y; }

  explicit operator Point () const { return {_x, _y}; }

  operator Toto() const { return {_x, _y}; }

 private:
  double _x, _y;
};

template < typename T >
void print(const T& t) {
  std::cout << "[x : " << t.x() << " ; y: " << t.y() << "] \n";
}

}

int main () {

  Test::Coord coord(2.0, 3.0);

  // For CLion users
  // https://youtrack.jetbrains.com/issue/CPP-569
  auto point = static_cast<Test::Point>(coord);

  Test::Toto toto = coord;

  Test::print(coord);
  Test::print(point);
  Test::print(toto);

  return 0;
}

// conversion.cpp ends here
