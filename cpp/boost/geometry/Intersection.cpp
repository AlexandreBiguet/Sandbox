/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

/**
 * Testing boost::geometry::intersection algo
 * should be the '&&' operation
 *
 * Input 1 : a green polygon
 * Input 2 : a blue polygon
 * Output  : intersection of green and blue = red
 */

#include <fstream>
#include <iostream>
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

typedef boost::geometry::model::d2::point_xy<double> point2d;
typedef boost::geometry::model::polygon<point2d> polygon;

void printPolygon(const std::string &filename, const std::string &map,
                  const polygon &poly) {
  std::ofstream svg(filename);
  boost::geometry::svg_mapper<point2d> mapper(svg, 500, 500);
  mapper.add(poly);
  mapper.map(poly, map);
}

void print(const polygon &green, const polygon &blue,
           const std::vector<polygon> &vp) {
  std::ofstream svg("boost-geometry-intersection-complicated.svg");

  boost::geometry::svg_mapper<point2d> mapper(svg, 400, 400);

  mapper.add(green);
  mapper.map(green, "fill-opacity:0.5;stroke:rgb(0,255,0);fill:rgb(0,255,0)");

  mapper.add(blue);
  mapper.map(blue, "fill-opacity:0.5;stroke:rgb(0,0,255);fill:rgb(0,0,255)");

  for (const auto &i : vp) {
    mapper.add(i);
    mapper.map(i, "fill-opacity:0.5;stroke:rgb(255,0,0);fill:rgb(255,0,0)");
  }
}

int main() {
  polygon green, blue;

  boost::geometry::read_wkt(
      "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 "
      "1.2,4.9 0.8,2.9 0.7,2 1.3)"
      "(4.0 2.0, 4.2 1.4, 4.8 1.9, 4.4 2.2, 4.0 2.0))",
      green);

  boost::geometry::read_wkt(
      "POLYGON((4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , "
      "6.0 1.5 , 4.5 1.0 , 4.0 -0.5))",
      blue);

  std::vector<polygon> output;
  boost::geometry::intersection(green, blue, output);

  print(green, blue, output);

  printPolygon("boost-geometry-intersection-complicated-output.svg",
               "fill-opacity:0.5;stroke:rgb(255,0,0);fill:rgb(255,0,0)",
               output[0]);

  return 0;
}

// Intersection.cpp ends here
