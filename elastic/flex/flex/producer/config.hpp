//
//
//

#pragma once

#include <string>
#include <memory>

namespace flex { namespace producer {

struct Config {
  explicit Config(std::string &&target, std::size_t period_ms = 300);

  std::string _target;
  std::size_t _period_ms;
};


}}
