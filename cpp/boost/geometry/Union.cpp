/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#include <fstream>
#include <iostream>
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

int main() {
  typedef boost::geometry::model::d2::point_xy<double> point2D;
  typedef boost::geometry::model::polygon<point2D> polygon;

  polygon green, blue;

  boost::geometry::read_wkt(
      "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4"
      " 1.2,4.9 0.8,2.9 0.7,2 1.3) (4.0 2.0, 4.2 1.4, 4.8 1.9, 4.4 2.2, 4.0"
      " 2.0))",
      green);

  boost::geometry::read_wkt(
      "POLYGON((4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , "
      " 6.0 1.5 , 4.5 1.0 , 4.0 -0.5))",
      blue);

  std::vector<polygon> output;
  boost::geometry::union_(blue, green, output);

  std::cout << " output size : " << output.size() << std::endl;

  {
    std::ofstream svg("boost-geometry-union.svg");

    boost::geometry::svg_mapper<point2D> mapper(svg, 100, 100);

    mapper.add(green);
    mapper.map(green,
               "fill-opacity:0.5;stroke:rgb(50,205,50);"
               "fill:rgb(50,205,50)");

    mapper.add(blue);
    mapper.map(blue,
               "fill-opacity:0.5;stroke:rgb(0,191,255);"
               "fill:rgb(0,191,255)");
  }

  if (!output.empty()) {
    std::ofstream svg("boost-geometry-union-output.svg");

    boost::geometry::svg_mapper<point2D> mapper(svg, 100, 100);

    mapper.add(output[0]);
    mapper.map(output[0],
               "fill-opacity:0.5;stroke:rgb(50,205,50);"
               "fill:rgb(50,205,50)");
  }

  return 0;
}

// Union.cpp ends here
