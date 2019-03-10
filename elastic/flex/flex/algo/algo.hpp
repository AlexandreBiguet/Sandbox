//
//
//

#pragma once

#include "stat.hpp"

namespace flex {
namespace algo {

/// \brief
/// \tparam Iter
/// \tparam Container
/// \param begin
/// \param end
/// \return
template <typename Iter,
          template <typename, typename> class Container = std::vector>
Container<typename std::iterator_traits<Iter>::value_type,
          std::allocator<typename std::iterator_traits<Iter>::value_type>>
zscore(Iter begin, Iter end) {

  using ValueType = typename std::iterator_traits<Iter>::value_type;

  RStat stat(begin, end);
  Container<ValueType, std::allocator<ValueType>> container;
  container.reserve(std::distance(begin, end));
  auto mean = stat.mean();
  auto stddev = stat.stddev();

  for (auto it = begin; it != end; ++it) {
    container.emplace_back((*it - mean) / stddev);
  }

  return container;
}

} // namespace algo
} // namespace flex
