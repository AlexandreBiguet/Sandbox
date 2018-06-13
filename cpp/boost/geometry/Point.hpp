/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#pragma once

#include <iostream>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

namespace Geometry {
namespace Euclidean {
namespace test {

class Point2D : public boost::geometry::model::d2::point_xy<double> {
 public:
  void print() { std::cout << " bonjour :" << x() << " " << y() << std::endl; }
};

}  // namespace test
}  // namespace Euclidean
}  // namespace Geometry

// Defining traits for this point
// http://www.boost.org/doc/libs/1_61_0/libs/geometry/doc/html/geometry/reference/concepts/concept_point.html

// See
// http://www.boost.org/doc/libs/1_54_0/libs/geometry/doc/html/geometry/examples/example_source_code__adapting_a_legacy_geometry_object_model.html
// For example

// And
// http://stackoverflow.com/questions/18061728/how-to-inherit-from-boostgeometrymodelpoint

namespace boost {
namespace geometry {
namespace traits {

template <>
struct tag<Geometry::Euclidean::test::Point2D> {
  typedef point_tag type;
};

template <>
struct coordinate_type<Geometry::Euclidean::test::Point2D> {
  typedef double type;
};

template <>
struct coordinate_system<Geometry::Euclidean::test::Point2D> {
  typedef boost::geometry::cs::cartesian type;
};

template <>
struct dimension<Geometry::Euclidean::test::Point2D> : boost::mpl::int_<2> {};

template <std::size_t I>
struct access<Geometry::Euclidean::test::Point2D, I> {
  static inline double get(Geometry::Euclidean::test::Point2D const& p) {
    return p.template get<I>();
  }

  static inline void set(Geometry::Euclidean::test::Point2D& p,
                         double const& v) {
    p.template set<I>(v);
  }
};

}  // namespace traits
}  // namespace geometry
}  // namespace boost

// Point.hpp ends here
