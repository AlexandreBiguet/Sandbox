//
//  geodesic.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 17/05/2018 at 16:59.
//  Copyright © 2018 UAVIA. All rights reserved.
//

#include <cmath>
#include <iostream>

#include <GeographicLib/Geodesic.hpp>

static double earthRadius_m = 6371000.0;
static double degToRad = M_PI / 180.0;

struct Point {
  Point(double lat, double lon) : _lat(lat), _lon(lon) { }
  double latitude() const { return _lat; }
  double longitude() const { return _lon; }

  double _lat;
  double _lon;
};

double haversine(const Point& p1, const Point& p2) {
  double lat1 = p1.latitude() * degToRad;
  double lon1 = p1.longitude() * degToRad;

  double lat2 = p2.latitude() * degToRad;
  double lon2 = p2.longitude() * degToRad;

  double dlat = 0.5 * (lat2 - lat1);
  double dlon = 0.5 * (lon2 - lon1);

  double slat = sin(dlat);
  double slat2 = slat * slat;

  double slon = sin(dlon);
  double slon2 = slon * slon;

  double temp = slat2 + cos(lat1) * cos(lat2) * slon2;
  temp = sqrt(temp);

  return 2.0 * earthRadius_m * asin(temp);
}

double geodesic (const Point& p1, const Point& p2) {
  GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                               GeographicLib::Constants::WGS84_f());
  double len;
  geod.Inverse(p1.latitude(), p1.longitude(), p2.latitude(), p2.longitude(),
               len);
  return len;
}

int main () {

  Point newyork(40.730610, -73.935242);
  Point paris (48.864716, 2.349014);

  double l1 = haversine(paris, newyork);
  double l2 = geodesic(paris, newyork);

  std::cout << "haversine : " << l1 << "\n";
  std::cout << "geodesic  : " << l2 << "\n";

  return 0;
}

// geodesic.cpp ends here