/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

/**
 * Check the result of the boost::geometry::overlaps
 *
 * Let's define G a geometry object
 * Let I(G) be the interior of G
 * Let E(G) be the exterior of G
 * Let B(G) be the boundary of G
 *
 * 1st case : the green and blue polygons do overlap in the OGC sense :
 *   I(green) && I(blue) != empty
 *   I(green) && E(blue) != empty
 *   E(green) && I(blue) != empty
 * output : boost-geom-overlaps-case1.svg
 *
 * 2nd case : blue polygon is totally contained in green polygon
 *  -> overlaps should return false
 *
 * 3rd case : blue and green polygon are identical. my guess is that
 * depending on the boost strategy, the overlaps function may return
 * true or false With the default strategy -> result is false
 *
 * 4th case : blue and green are far away one to the other
 */

#include <fstream>
#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

typedef boost::geometry::model::d2::point_xy<double> point2d;
typedef boost::geometry::model::polygon<point2d> polygon;

void print(const std::string &filename, const polygon &green,
           const polygon &blue) {
  std::ofstream svg(filename);

  boost::geometry::svg_mapper<point2d> mapper(svg, 500, 500);

  mapper.add(green);
  mapper.map(green, "fill-opacity:0.5;stroke:rgb(0,255,0);fill:rgb(0,255,0)");

  mapper.add(blue);
  mapper.map(blue, "fill-opacity:0.5;stroke:rgb(0,0,255);fill:rgb(0,0,255)");
}

int main() {
  int status(0);

  {
    // Case I

    polygon green, blue;

    boost::geometry::read_wkt("POLYGON((0 0, 3 0, 3 3, 0 3, 0 0))", green);
    boost::geometry::read_wkt(
        "POLYGON((0.5 0.5, 3.5 0.5, 3.5 3.5, 0.5 3.5, 0.5 0.5))", blue);

    if (!boost::geometry::overlaps(green, blue)) {
      std::cout << " ==> boost::geometry::overlaps function does not work as "
                   "expected 1 a\n";
      ++status;
    }

    if (!boost::geometry::overlaps(blue, green)) {
      std::cout << " ==> boost::geometry::overlaps function does not work as "
                   "expected 1 b\n";
      ++status;
    }

    print("boost-geom-overlaps-case1.svg", green, blue);
  }

  {
    // Case II

    polygon green, blue;

    boost::geometry::read_wkt("POLYGON((0 0, 5 0, 5 5, 0 5, 0 0))", green);
    boost::geometry::read_wkt("POLYGON((1 1, 4 1, 4 4, 1 4, 1 1))", blue);

    if (boost::geometry::overlaps(green, blue)) {
      std::cout << " ==> boost::geometry::overlaps function does not work as "
                   "expected 2 a\n";
      ++status;
    }

    if (boost::geometry::overlaps(blue, green)) {
      std::cout << " ==> boost::geometry::overlaps function does not work as "
                   "expected 2 b \n";
      ++status;
    }

    print("boost-geom-overlaps-case2.svg", green, blue);
  }

  {
    // Case III

    polygon green, blue;

    boost::geometry::read_wkt("POLYGON((0 0, 5 0, 5 5, 0 5, 0 0))", green);
    boost::geometry::read_wkt("POLYGON((0 0, 5 0, 5 5, 0 5, 0 0))", blue);

    if (boost::geometry::overlaps(green, blue)) {
      std::cout << " ==> boost::geometry::overlaps function does not work as "
                   "expected 3 a\n";
      ++status;
    }

    if (boost::geometry::overlaps(blue, green)) {
      std::cout << " ==> boost::geometry::overlaps function does not work as "
                   "expected 3 b \n";
      ++status;
    }

    print("boost-geom-overlaps-case3.svg", green, blue);
  }

  {
    // Case IV

    polygon green, blue;

    boost::geometry::read_wkt(
        "POLYGON((-10 -10, -15 -10, -15 -15, -10 -15, -10 -10))", green);
    boost::geometry::read_wkt("POLYGON((5.5 5.5, 7 5, 7 7, 5 7, 5 5))", blue);

    if (boost::geometry::overlaps(green, blue)) {
      std::cout << " ==> boost::geometry::overlaps function does not work as "
                   "expected 4 a\n";
      ++status;
    }

    if (boost::geometry::overlaps(blue, green)) {
      std::cout << " ==> boost::geometry::overlaps function does not work as "
                   "expected 4 b \n";
      ++status;
    }

    print("boost-geom-overlaps-case4.svg", green, blue);
  }

  if (status == 0) {
    std::cout << "boost::geometry::overlaps function works as expected \n";
  }

  return 0;
}

// Overlaps.cpp ends here
