/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   16 - Nov - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 16 - Nov - 2018
 */

#include <iostream>

#include <boost/concept/usage.hpp>
#include <boost/concept_check.hpp>

template <bool isRelative = true>
struct PanAngle {
  using Relative = bool;
  Relative _relative = isRelative;
};

template <bool isRelative = true>
struct TiltAngle {
  using Relative = bool;
  Relative _relative = isRelative;
};

struct CoucouAngle {};

template <typename T>
struct AngleTypeConcept {
 public:
  BOOST_CONCEPT_USAGE(AngleTypeConcept) { typename T::Relative a; }

 private:
  T t;
};

// template <template <typename> class Type>
template <typename Type>
class Angle {
  BOOST_CONCEPT_ASSERT((AngleTypeConcept<Type>));

 public:
  Angle() = default;
  Angle(double value) : _value(value) {}
  double value() const { return _value; }
  bool relative() const { return _angle._relative; }

  void set(double value, bool relative);

 private:
  double _value{0.0};
  Type _angle;
};

int main() {
  //  Angle<double> angle(12.0);

  {
    Angle<TiltAngle<true>> angle(12.0);
    assert(true == angle.relative());
  }

  {
    Angle<TiltAngle<false>> angle(12.0);
    assert(false == angle.relative());
  }

  {
    Angle<PanAngle<true>> angle(12.0);
    assert(true == angle.relative());
  }

  {
    Angle<PanAngle<false>> angle(12.0);
    assert(false == angle.relative());
  }

  // Angle<double> angle(12.0);
  // Angle<CoucouAngle> angle(12.0);

  std::cout << " ---> All right \n";

  return 0;
}
