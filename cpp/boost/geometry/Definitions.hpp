/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#pragma once

#include <boost/geometry.hpp>

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

using BoostPoint2D = BoostPoint<2>;
using BoostPoint3D = BoostPoint<3>;

using BoostPolygon2D = BoostPolygon<BoostPoint2D>;
using BoostLineString2D = BoostLineString<BoostPoint2D>;
using BoostLineString3D = BoostLineString<BoostPoint3D>;
using BoostRing2D = BoostRing<BoostPoint2D>;
using BoostBox2D = boost::geometry::model::box<BoostPoint2D>;

namespace bg = boost::geometry;

// Definitions.hpp ends here
