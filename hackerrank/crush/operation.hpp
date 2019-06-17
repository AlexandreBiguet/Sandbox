#pragma once

#include "interval.hpp"

#include <vector>

namespace crush {

template <typename T>
struct Operation_t {
  Interval_t<T> _interval;
  T _value;

  Operation_t(const Interval_t<T>& interval, const T& value) : _interval(interval), _value(value) {}
  Operation_t(const T& low, const T& high, const T& value) : Operation_t(Interval_t<T>{low, high}, value) {}
  explicit Operation_t(const std::vector<T>& vec) : Operation_t(vec[0], vec[1], vec[2]) {}
};

template <typename T>
stdx::optional<Operation_t<T>> intersects(const Operation_t<T>& o1, const Operation_t<T>& o2) {
  auto inter = intersects(o1._interval, o2._interval);
  if (inter) {
    return Operation_t<T>(*inter, o1._value + o2._value);
  }
  return stdx::optional<Operation_t<T>>();
}

template <typename T>
void print(const Operation_t<T>& op, std::ostream& stream = std::cout) {
  stream << "[ " << op._interval._low << " , " << op._interval._high << " ] : " << op._value << "\n";
}

template <typename T>
void print(const std::vector<Operation_t<T>>& ops, std::ostream& stream = std::cout) {
  for (const auto& op : ops) {
    print(op, stream);
  }
}

template <typename T>
bool within(const Operation_t<T>& o, const T& value) {
  return within(o._interval, value);
}

using Operation = Operation_t<int>;

}  // namespace crush
