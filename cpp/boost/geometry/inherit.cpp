//
//  inherit.cpp
//  Sandbox
//
//  Created by Alexandre Biguet on 26/04/2018 at 09:33.
//  Copyright © 2018
//

#include <iostream>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/ring.hpp>

namespace Test {

using BCartesian = boost::geometry::cs::cartesian;

template <std::size_t Dim>
using BPoint = boost::geometry::model::point<double, Dim, BCartesian>;

template <typename PointType>
using BRing = boost::geometry::model::ring<PointType, true>;

template <typename Point>
class Ring : public BRing<Point> {
 public:
  Ring() = default;

  template <typename Iter>
  Ring(Iter begin, Iter end) : BRing<Point>(begin, end) {}
};

}  // namespace Test

template <typename Point>
void print(const Point& p) {
  std::cout << "[ " << boost::geometry::get<0>(p) << " ; "
            << boost::geometry::get<1>(p) << " ] \n";
}

int main() {
  Test::Ring<Test::BPoint<2>> ring;
  ring.push_back({0.0, 0.0});
  ring.push_back({1.0, 0.0});
  ring.push_back({1.0, 1.0});
  ring.push_back({0.0, 1.0});
  ring.push_back({0.0, 0.0});

  for (const auto& elem : ring) {
    print(elem);
  }

  std::cout << "\n";

  Test::BRing<Test::BPoint<2>> ring1;
  ring1.push_back({0.0, 0.0});
  ring1.push_back({1.0, 0.0});
  ring1.push_back({0.0, 0.0});

  for (const auto& elem : ring1) {
    print(elem);
  }

  return 0;
}

// inherit.cpp ends here
