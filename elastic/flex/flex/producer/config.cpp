#include "config.hpp"

namespace flex {
namespace producer {

// ----------------------------------------------------------------------------

Config::Config(std::string &&target, std::size_t period_ms)
    : _target(std::move(target)), _period_ms(period_ms) {}

// ----------------------------------------------------------------------------

} // namespace producer
} // namespace flex