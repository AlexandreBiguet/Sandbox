/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <boost/assign.hpp>

template <typename Segment>
struct gather_segment_statistics {
  // Remember that if coordinates are integer, the length might be floating
  // point So use "double" for integers. In other cases, use coordinate type
  typedef typename boost::geometry::select_most_precise<
      typename boost::geometry::coordinate_type<Segment>::type, double>::type
      type;

  type min_length, max_length;

  // Initialize min and max
  gather_segment_statistics() : min_length(1e38), max_length(-1) {}

  // This operator is called for each segment
  inline void operator()(Segment const& s) {
    type length = boost::geometry::length(s);
    if (length < min_length) min_length = length;
    if (length > max_length) max_length = length;
  }
};

int main() {
  // Bring "+=" for a vector into scope
  using namespace boost::assign;

  // Define a type
  typedef boost::geometry::model::d2::point_xy<double> point;

  // Declare a linestring
  boost::geometry::model::linestring<point> polyline;

  // Use Boost.Assign to initialize a linestring
  polyline += point(0, 0), point(3, 3), point(5, 1), point(6, 2), point(8, 0),
      point(4, -4), point(1, -1), point(3, 2);

  // Declare the gathering class...
  gather_segment_statistics<boost::geometry::model::referring_segment<point> >
      functor;

  // ... and use it, the essention.
  // As also in std::for_each it is a const value, so retrieve it as a return
  // value.
  functor = boost::geometry::for_each_segment(polyline, functor);

  // Output the results
  std::cout << "Min segment length: " << functor.min_length << std::endl
            << "Max segment length: " << functor.max_length << std::endl;

  return 0;
}

// ForEachSegmentTuto.cpp ends here
