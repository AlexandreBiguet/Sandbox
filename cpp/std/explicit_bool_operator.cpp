//
//  explicit_bool_operator.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 06/09/2018 at 12:30.
//

/// Does making 'explicit' a bool operator allow me to write :
/// if (instance) { ... }
/// ??

/// Answer : yes :-)

#include <iostream>

class Class {
 public:

  Class() : Class(false) {}

  explicit Class(double val) : Class(true, val){ }

  operator bool() const { return _valid; }

 private:
  explicit Class (bool valid, double val = 0.0) : _valid(valid), _val(0.0) { }
  bool _valid;
  double _val;
};

class Class2 {
 public:

  Class2() : Class2(false) {}

  explicit Class2(double val) : Class2(true, val) { }

  explicit operator bool() const { return _valid; }

 private:
  explicit Class2 (bool valid, double val = 0.0) : _valid(valid), _val(0.0) { }
  bool _valid;
  double _val;
};

int main() {

  Class c;

  if (c) {
    std::cout << "this should not happen " << __LINE__ << "\n";
  }

  Class2 c2;

  if (c2) {
    std::cout << "this should not happen " << __LINE__ << "\n";
  }

  if (c == true) {
    std::cout << "this should not happen " << __LINE__ << "\n";
  }

/*
 * The explicit bool operator takes its value here :-)
 *

  if (c2 == true) {
    std::cout << "this should not happen " << __LINE__ << "\n";
  }

*/
  return 0;
}
// explicit_bool_operator.cpp ends here