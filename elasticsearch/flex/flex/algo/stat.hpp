//
//
//

#pragma once

#include <array>

namespace flex {
namespace algo {

class RStat {

 public:

  using ValueType = double;

  RStat() = default;

  template <typename Iter>
  RStat(Iter begin, Iter end) {
    push(begin, end);
  }

  template <typename Iter>
  void push(Iter begin, Iter end) {
    for (auto it = begin; it != end; ++it) {
      push(*it);
    }
  }

  void push(const ValueType& value);
  void clear();
  ValueType min() const;
  ValueType max() const;
  ValueType mean() const;
  ValueType variance() const;
  ValueType stddev() const;
  ValueType rms() const;
  ValueType skew() const;
  ValueType kurt() const;

  std::size_t size() const;

 private:
  std::size_t _size{0};
  ValueType _min{0.0};
  ValueType _max{0.0};
  std::array<ValueType, 4> _moments{0.0, 0.0, 0.0, 0.0};
};

}}
