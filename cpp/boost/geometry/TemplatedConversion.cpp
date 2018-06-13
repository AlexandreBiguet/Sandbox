/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#include <iostream>

#include <boost/geometry.hpp>

template <typename Type>
using BaseContainer = std::vector<Type>;

template <typename PointType>
using PolygonContainer = BaseContainer<BaseContainer<PointType>>;

using BoostCartesian = boost::geometry::cs::cartesian;

template <std::size_t Dim>
using BoostPoint = boost::geometry::model::point<double, Dim, BoostCartesian>;

/**
 * NOTE : the template parameter PointType must be a point type known to
 * boost::geometry (i.e. PointType must have boost::geometry::point traits)
 */
template <typename PointType>
using BoostPolygon = boost::geometry::model::polygon<PointType>;

template <typename PointType>
using BoostLineString = boost::geometry::model::linestring<PointType>;

template <typename PointType>
using BoostRing = boost::geometry::model::ring<PointType>;

template <typename PointType>
using BoostBox = boost::geometry::model::box<PointType>;

/**
 * Converts a 'one layer' boost geometry into a vector of PointType
 * */
template <typename Geometry, typename PointType>
void convert(BaseContainer<PointType>& dest, const Geometry& src) {
  dest.clear();

  for (auto it = boost::begin(src); it != boost::end(src); ++it) {
    dest.push_back(*it);
  }
}

/**
 * Prints a boost 2D point to stdcout
 * */

void print(const BoostPoint<2>& pt) {
  std::cout << "(" << boost::geometry::get<0>(pt) << ", "
            << boost::geometry::get<1>(pt) << ")\n";
}

namespace bg = boost::geometry;

int main() {
  {
    std::cout << "Testing with boost line string\n";

    std::cout << "Should print : \n(0, 0)\n(1, 1)\n(2, 2)\n\n";

    BoostLineString<BoostPoint<2>> line;

    bg::append(line, BoostPoint<2>(0.0, 0.0));
    bg::append(line, BoostPoint<2>(1.0, 1.0));
    bg::append(line, BoostPoint<2>(2.0, 2.0));

    BaseContainer<BoostPoint<2>> vec;

    convert(vec, line);

    for (const auto& it : vec) {
      print(it);
    }
  }

  {
    std::cout << "\nTesting with boost ring\n";

    std::cout << "Should print : \n(0, 0)\n(1, 1)\n(2, 2)\n\n";

    BoostRing<BoostPoint<2>> ring;

    bg::append(ring, BoostPoint<2>(0.0, 0.0));
    bg::append(ring, BoostPoint<2>(1.0, 1.0));
    bg::append(ring, BoostPoint<2>(2.0, 2.0));

    BaseContainer<BoostPoint<2>> vec;

    convert(vec, ring);

    for (const auto& it : vec) {
      print(it);
    }
  }

  return 0;
}

// TemplatedConversion.cpp ends here
