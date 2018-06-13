/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#include "Point.hpp"

namespace Geometry {
namespace Euclidean {
namespace Cartesian {

template <std::size_t dim>
class Point
    : public boost::geometry::model::point<double, dim,
                                           boost::geometry::cs::cartesian> {
 public:
  void print();
};

}  // namespace Cartesian
}  // namespace Euclidean
}  // namespace Geometry

namespace boost {
namespace geometry {
namespace traits {

template <std::size_t dim>
struct tag<Geometry::Euclidean::Cartesian::Point<dim> > {
  typedef point_tag type;
};

template <std::size_t dim>
struct coordinate_type<Geometry::Euclidean::Cartesian::Point<dim> > {
  typedef double type;
};

template <std::size_t dim>
struct coordinate_system<Geometry::Euclidean::Cartesian::Point<dim> > {
  typedef boost::geometry::cs::cartesian type;
};

template <std::size_t dim>
struct dimension<Geometry::Euclidean::Cartesian::Point<dim> > {
  static const std::size_t value = dim;
};

template <std::size_t dim, std::size_t I>
struct access<Geometry::Euclidean::Cartesian::Point<dim>, I> {
  static inline double get(
      Geometry::Euclidean::Cartesian::Point<dim> const& p) {
    return p.template get<I>();
  }

  static inline void set(Geometry::Euclidean::Cartesian::Point<dim>& p,
                         double const& v) {
    p.template set<I>(v);
  }
};

}  // namespace traits
}  // namespace geometry
}  // namespace boost

namespace Geometry {
namespace Euclidean {
namespace Cartesian {

template <>
class Point<3>
    : public boost::geometry::model::point<double, 3,
                                           boost::geometry::cs::cartesian> {
 public:
  void print() {
    std::cout << boost::geometry::get<0>(*this) << " "
              << boost::geometry::get<1>(*this) << " "
              << boost::geometry::get<2>(*this) << "\n";
  }
};

template <>
class Point<2>
    : public boost::geometry::model::point<double, 2,
                                           boost::geometry::cs::cartesian> {
 public:
  void print() {
    std::cout << boost::geometry::get<0>(*this) << " "
              << boost::geometry::get<1>(*this) << "\n";
  }
};

typedef Point<2> Point2;
typedef Point<3> Point3;

}  // namespace Cartesian
}  // namespace Euclidean
}  // namespace Geometry

int main() {
  /**
   * testing custom point definition in Point.hpp
   * */

  Geometry::Euclidean::test::Point2D p;
  p.print();
  boost::geometry::set<0>(p, 1.0);
  boost::geometry::set<1>(p, 0.2);
  p.print();
  boost::geometry::model::d2::point_xy<double> p2(10.0, 5.0);
  boost::geometry::assign_point(p, p2);
  p.print();
  std::cout << " toto :" << p.x() << " " << p.y() << std::endl;

  Geometry::Euclidean::Cartesian::Point<3> p3;  // ( 1.0, 2.0, 3.0 );
  boost::geometry::set<0>(p3, 1.0);
  boost::geometry::set<1>(p3, 2.0);
  boost::geometry::set<2>(p3, 3.0);
  p3.print();
  std::cout << std::endl;

  Geometry::Euclidean::Cartesian::Point2 p4;  // (1.0, 2.0 );
  boost::geometry::set<0>(p4, 10.0);
  boost::geometry::set<1>(p4, 20.0);
  p4.print();

  return 0;
}

// Point.cpp ends here
