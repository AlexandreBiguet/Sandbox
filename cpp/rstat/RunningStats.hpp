//
//  RunningStats.hpp
//
//  Created by Alexandre Biguet
//
#pragma once

#include <cmath>
#include <vector>

/// \brief this is a helper class to compute running statistic
class RunningStats {
public:
  explicit RunningStats(
      const std::vector<double> &init_data = std::vector<double>());

  void update(double x);
  void clear();

  double min() const;
  double max() const;
  double mean() const;
  double variance() const;
  double standardDeviation() const;
  double rootMeanSquare() const;
  double skew() const;
  double kurt() const;

  size_t n() const;

private:
  double _min, _max, _m1, _m2, _m3, _m4;
  size_t _n;
};


// RunningStats.hpp ends here