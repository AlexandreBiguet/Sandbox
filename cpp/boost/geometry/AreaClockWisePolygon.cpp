/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#include <iostream>

#include <boost/geometry.hpp>

namespace bg = boost::geometry;

/**
 *
 * The default boost geometry polygon is clockwise oriented
 * meaning that its outer ring is clock wise and that any of
 * its inner rings is counterclockwise.
 *
 * By definition, the area of a convex polygon is defined to be
 * positive if the points are arranged in a counterclockwise order,
 * and negative if they are in clockwise order (Beyer 1987).
 * (Ref. http://mathworld.wolfram.com/PolygonArea.html)
 *
 *
 * From the doc :
 * http://www.boost.org/doc/libs/1_66_0/libs/geometry/doc/html/geometry/reference/models/model_polygon.html
 * The input polygon respects the clockwise orientation :
 * outer ring is constructed clockwise and its single inner ring is
 * counterclockwise
 *
 *
 * CONCLUSION :
 * ------------
 * The boost geometry models polygon and rings take a Clockwise bool template
 * parameter.
 *
 * In the case of a clockwise geometry which is indeed constructed with
 * clockwise element, the area is positive
 * -> In the following program, the polygon_t polygon2 has the template
 * parameter Clockwise = True and its outer ring is clockwise and its inner ring
 * is counter clock wise. Its area is then positive.
 *
 * This is the same thing for the ring_t r1 and r2 (both have template parameter
 * Clockwise = true) r1 is constructed clockwise -> its area is positive r2 is
 * constructed counterclockwise -> its area is negative
 *
 *
 *
 * @return 0 if SUCCESS
 */

int main(void) {
  typedef bg::model::point<double, 2, bg::cs::cartesian> point_t;
  typedef bg::model::polygon<point_t, true> polygon_t;
  typedef bg::model::ring<point_t, true> ring_t;

  polygon_t polygon2{
      {{0.0, 0.0}, {0.0, 5.0}, {5.0, 5.0}, {5.0, 0.0}, {0.0, 0.0}},
      {{1.0, 1.0}, {4.0, 1.0}, {4.0, 4.0}, {1.0, 4.0}, {1.0, 1.0}}};

  ring_t r1{{0.0, 0.0}, {0.0, 5.0}, {5.0, 5.0}, {5.0, 0.0}, {0.0, 0.0}};
  ring_t r2{{1.0, 1.0}, {4.0, 1.0}, {4.0, 4.0}, {1.0, 4.0}, {1.0, 1.0}};

  double area = boost::geometry::area(polygon2);

  std::cout << " polygon area : " << area << std::endl;

  area = boost::geometry::area(r1);
  std::cout << " ring 1 area : " << area << std::endl;

  area = boost::geometry::area(r2);
  std::cout << " ring 2 area : " << area << std::endl;

  return 0;
}

// AreaClockWisePolygon.cpp ends here
