//
//  RunningStats.cpp
//
//  Created by Alexandre Biguet
//

#include "RunningStats.hpp"

// ----------------------------------------------------------------------------

RunningStats::RunningStats(const std::vector<double> &init_data) {
  clear();

  for (const auto &elem : init_data) {
    update(elem);
  }
}

// ----------------------------------------------------------------------------

void RunningStats::update(double x) {
  double m = mean();
  double delta = x - m;
  double delta_n, delta_nsq, term1, n;

  // update min and max
  if (_n == 0) {
    _min = x;
    _max = x;
  } else {
    if (x < _min) {
      _min = x;
    }
    if (x > _max) {
      _max = x;
    }
  }

  // update moments

  ++_n;
  n = static_cast<double>(_n);

  delta_n = delta / n;

  delta_nsq = delta_n * delta_n;

  term1 = delta * delta_n * (n - 1.0);

  _m1 += delta_n;

  _m4 += term1 * delta_nsq * (n * n - 3.0 * n + 3.0) + 6.0 * delta_nsq * _m2 -
         4.0 * delta_n * _m3;

  _m3 += term1 * delta_n * (n - 2.0) - 3.0 * delta_n * _m2;

  _m2 += term1;
}

// ----------------------------------------------------------------------------

void RunningStats::clear() {
  _min = 0.;
  _max = 0.;
  _m1 = 0.;
  _m2 = 0.;
  _m3 = 0.;
  _m4 = 0.;
  _n = 0;
}

// ----------------------------------------------------------------------------

double RunningStats::min() const { return _min; }

// ----------------------------------------------------------------------------

double RunningStats::max() const { return _max; }

// ----------------------------------------------------------------------------

double RunningStats::mean() const { return _m1; }

// ----------------------------------------------------------------------------

double RunningStats::variance() const {
  if (_n > 1) {
    return (_m2 / (static_cast<double>(_n) - 1.0));
  }
  return 0.;
}

// ----------------------------------------------------------------------------

double RunningStats::standardDeviation() const { return sqrt(variance()); }

// ----------------------------------------------------------------------------

double RunningStats::rootMeanSquare() const {
  double rms(0.0);

  if (_n > 0) {
    double m = mean();
    double s = standardDeviation();
    auto n = static_cast<double>(_n);
    double a = sqrt((n - 1.0) / n);
    rms = std::hypot(m, a * s);
  }

  return rms;
}

// ----------------------------------------------------------------------------

double RunningStats::skew() const {
  if (_n > 0) {
    auto n = static_cast<double>(_n);
    double fac = std::pow(n - 1.0, 1.5) / n;
    return ((fac * _m3) / pow(_m2, 1.5));
  }
  return 0.0;
}

// ----------------------------------------------------------------------------

double RunningStats::kurt() const {
  if (_n > 0) {
    auto n = static_cast<double>(_n);
    double fac = ((n - 1.0) / n) * (n - 1.0);
    return ((fac * _m4) / (_m2 * _m2) - 3.0);
  }
  return 0.0;
}

// ----------------------------------------------------------------------------

size_t RunningStats::n() const { return _n; }

// RunningStats.cpp ends here