#pragma once

#include <iostream>

#if __has_include(<optional>)
#include <optional>
namespace stdx {
using namespace ::std;
}
#elif __has_include(<experimental/optional>)
#include <experimental/optional>
namespace stdx {
using namespace ::std;
using namespace ::std::experimental;
}  // namespace stdx
#else
#error <experimental/optional> and <optional> not found
#endif

namespace crush {

// Should use boost::interval
template <typename T>
struct Interval_t {
  T _low;
  T _high;

  Interval_t(const T& l, const T& h) : _low(l), _high(h) {
    if (_high < _low) {
      std::swap(_high, _low);
    }
  }
};

template <typename T>
bool overlap(const Interval_t<T>& i1, const Interval_t<T>& i2) {
  // overlap means, \exists c so that:
  // low_1 <= c <= high_1
  // and
  // low_2 <= c <= high_2
  // Equivalent to :
  return (i1._low <= i2._high && i2._low <= i1._high);
}

template <typename T>
stdx::optional<Interval_t<T>> intersects(const Interval_t<T>& i1, const Interval_t<T>& i2) {
  if (!overlap(i1, i2)) {
    return stdx::optional<Interval_t<T>>();
  }
  auto low = i1._low < i2._low ? i2._low : i1._low;
  auto high = i1._high < i2._high ? i1._high : i2._high;
  return Interval_t<T>(low, high);
}

template <typename T>
void print(const Interval_t<T>& i, std::ostream& stream = std::cout) {
  stream << "[ " << i._low << " , " << i._high << " ]\n";
}

template <typename T>
void print(const stdx::optional<Interval_t<T>>& i, std::ostream& stream = std::cout) {
  if (i) {
    print(*i, stream);
  } else {
    std::cout << "Invalid interval \n";
  }
}

template <typename T>
int width(const Interval_t<T>& i) {
  return i._high - i._low;
}

template <typename T>
bool within(const Interval_t<T>& i, const T& value) {
  return value <= i._high && value >= i._low;
}

using Interval = Interval_t<int>;

}  // namespace crush
