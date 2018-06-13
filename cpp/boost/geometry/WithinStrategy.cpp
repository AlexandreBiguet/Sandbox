/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

/**
 * Goals :
 *   1 - check how to use boost geometry within strategies
 *   2 - check which within strategy returns true when a point is located
 * exactly on the border of the geometry
 */

#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <boost/geometry/strategies/cartesian/point_in_poly_franklin.hpp>

int main() {
  typedef boost::geometry::model::d2::point_xy<double> point_type;
  typedef boost::geometry::model::ring<point_type> ring_type;

  ring_type ring{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 0}};
  point_type point{0, 0};

  if (boost::geometry::within(point, ring)) {
    std::cout << "Default strategy returned true" << std::endl;
  } else {
    std::cout << "Default strategy returned false" << std::endl;
  }

  if (boost::geometry::within(
          point, ring,
          boost::geometry::strategy::within::franklin<point_type>())) {
    std::cout << "franklin strategy returned true" << std::endl;
  } else {
    std::cout << "franklin strategy returned false" << std::endl;
  }

  return 0;
}

// WithinStrategy.cpp ends here
