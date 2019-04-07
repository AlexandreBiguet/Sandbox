//
//
//

#include "stat.hpp"

#include <cmath>

namespace flex {
namespace algo {

// ----------------------------------------------------------------------------

void RStat::push(const ValueType &value) {
  double m = mean();
  double delta = value - m;
  double delta_n, delta_nsq, term1, n;

  // update min and max
  if (_size == 0) {
    _min = value;
    _max = value;
  } else {
    if (value < _min) {
      _min = value;
    }
    if (value > _max) {
      _max = value;
    }
  }

  // update moments

  ++_size;
  n = static_cast<double>(_size);

  delta_n = delta / n;

  delta_nsq = delta_n * delta_n;

  term1 = delta * delta_n * (n - 1.0);

  _moments[0] += delta_n;

  _moments[3] += term1 * delta_nsq * (n * n - 3.0 * n + 3.0) +
                 6.0 * delta_nsq * _moments[1] - 4.0 * delta_n * _moments[2];

  _moments[2] += term1 * delta_n * (n - 2.0) - 3.0 * delta_n * _moments[1];

  _moments[1] += term1;
}

// ----------------------------------------------------------------------------

void RStat::clear() {
  _min = 0.;
  _max = 0.;
  std::for_each(std::begin(_moments), std::end(_moments),
                [](auto &e) { e = 0.0; });
  _size = 0;
}

// ----------------------------------------------------------------------------

RStat::ValueType RStat::min() const { return _min; }

// ----------------------------------------------------------------------------

RStat::ValueType RStat::max() const { return _max; }

// ----------------------------------------------------------------------------

RStat::ValueType RStat::mean() const { return _moments[0]; }

// ----------------------------------------------------------------------------

RStat::ValueType RStat::variance() const {
  if (_size > 1) {
    return (_moments[1] / (static_cast<double>(_size) - 1.0));
  }
  return 0.;
}

// ----------------------------------------------------------------------------

RStat::ValueType RStat::stddev() const { return std::sqrt(variance()); }

// ----------------------------------------------------------------------------

RStat::ValueType RStat::rms() const {
  double rms(0.0);

  if (_size > 0) {
    double m = mean();
    double s = stddev();
    auto n = static_cast<double>(_size);
    double a = std::sqrt((n - 1.0) / n);
    rms = std::hypot(m, a * s);
  }

  return rms;
}

// ----------------------------------------------------------------------------

RStat::ValueType RStat::skew() const {
  if (_size > 0) {
    auto n = static_cast<double>(_size);
    double fac = std::pow(n - 1.0, 1.5) / n;
    return ((fac * _moments[2]) / pow(_moments[1], 1.5));
  }
  return 0.0;
}

// ----------------------------------------------------------------------------

RStat::ValueType RStat::kurt() const {
  if (_size > 0) {
    auto n = static_cast<double>(_size);
    double fac = ((n - 1.0) / n) * (n - 1.0);
    return ((fac * _moments[3]) / (_moments[1] * _moments[1]) - 3.0);
  }
  return 0.0;
}

// ----------------------------------------------------------------------------

std::size_t RStat::size() const { return _size; }

// ----------------------------------------------------------------------------

} // namespace algo
} // namespace flex
