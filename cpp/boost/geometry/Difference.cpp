/**
 * In this program the `boost::geometry::difference` method is tested and the
 * results are plotted using the boost geometry svg utility.
 *
 * Testing boost::geometry::difference with two input polygon (one green and one
 * blue).
 *
 * The output polygon is red
 */

#include <fstream>
#include <iostream>
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

typedef boost::geometry::model::d2::point_xy<double> point2d;
typedef boost::geometry::model::polygon<point2d> polygon;
typedef boost::geometry::model::ring<point2d> ring;

size_t plotIter = 0;

void print(const polygon &green, const polygon &blue,
           const std::vector<polygon> &vp) {
  std::ofstream svg("boost-geometry-difference-complicated-" +
                    std::to_string(plotIter) + ".svg");
  plotIter++;

  boost::geometry::svg_mapper<point2d> mapper(svg, 200, 200);

  mapper.add(green);
  mapper.map(green, "fill-opacity:0.5;stroke:rgb(0,255,0);fill:rgb(0,255,0)");

  mapper.add(blue);
  mapper.map(blue, "fill-opacity:0.5;stroke:rgb(0,0,255);fill:rgb(0,0,255)");

  for (const auto &i : vp) {
    mapper.add(i);
    mapper.map(i, "fill-opacity:0.5;stroke:rgb(255,0,0);fill:rgb(255,0,0)");
  }
}

/**
 * Testing boost::geometry::difference with complicated shaped input polygons
 */
void differenceComplicatedShapes();

/**
 * Testing boost::geometry::difference with simple shaped input polygons
 */
void differenceSimpleShapes();

// --------------------------------------------------------------------
// main
// --------------------------------------------------------------------

int main() {
  // differenceComplicatedShapes();

  differenceSimpleShapes();

  return 0;
}

static void printPolygon(const std::string &filename, const std::string &map,
                         const polygon &poly) {
  std::ofstream svg(filename);
  boost::geometry::svg_mapper<point2d> mapper(svg, 500, 500);
  mapper.add(poly);
  mapper.map(poly, map);
}

void differenceSimpleShapes() {
  polygon green, blue;
  std::vector<polygon> output;

  std::cout << " Simple shaped polygons difference \n";

  boost::geometry::read_wkt("POLYGON((0 0, 3 0, 3 3, 0 3, 0 0))", green);

  boost::geometry::read_wkt(
      "POLYGON((0.5 0.5, 3.5 0.5, 3.5 3.5, 0.5 3.5, 0.5 0.5))", blue);

  boost::geometry::difference(green, blue, output);

  print(green, blue, output);

  printPolygon("boost-geometry-difference-simple-output-gb.svg",
               "fill-opacity:0.5;stroke:rgb(255,0,0);fill:rgb(255,0,0)",
               output[0]);

  output.clear();
  boost::geometry::difference(blue, green, output);

  print(green, blue, output);

  printPolygon("boost-geometry-difference-simple-output-bg.svg",
               "fill-opacity:0.5;stroke:rgb(255,0,0);fill:rgb(255,0,0)",
               output[0]);
}

void differenceComplicatedShapes() {
  polygon green, blue, outer, inner1, inner2;

  boost::geometry::read_wkt(
      "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6,"
      "5.4 1.2,4.9 0.8,2.9 0.7,2 1.3)"
      "(4.0 2.0, 4.2 1.4, 4.8 1.9, 4.4 2.2, 4.0 2.0))",
      green);

  boost::geometry::read_wkt(
      "POLYGON((4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , "
      "6.0 1.5 , 4.5 1.0 , 4.0 -0.5))",
      blue);

  std::vector<polygon> output;
  boost::geometry::difference(green, blue, output);

  print(green, blue, output);

  output.clear();
  boost::geometry::difference(blue, green, output);

  print(green, blue, output);

  boost::geometry::read_wkt("POLYGON((-4 4, -4 -4, 4 -4, 4 4, -4 4))", outer);

  boost::geometry::read_wkt("POLYGON((-3 3, -3 0, 0 0, 0 3, -3 3))", inner1);

  boost::geometry::read_wkt("POLYGON((-5 3, -5 0, 0 0, 0 3, -5 3))", inner2);

  output.clear();

  boost::geometry::difference(outer, inner1, output);
  print(outer, inner1, output);

  output.clear();

  boost::geometry::difference(inner1, outer, output);
  print(outer, inner1, output);

  output.clear();

  boost::geometry::difference(outer, inner2, output);
  print(outer, inner2, output);

  output.clear();

  boost::geometry::difference(inner2, outer, output);
  print(outer, inner2, output);
}

// difference.cpp ends here
