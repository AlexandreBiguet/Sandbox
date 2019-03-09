//
//
//

#pragma once

#include <memory>
#include <string>

namespace flex {
namespace producer {

struct Config {
  explicit Config(std::string &&index) : _index(std::move(index)) {}

  enum class IdGeneratorType { None, Incremental, Hash };

  std::string _index;
  std::size_t _period_ms{300};
  bool _requireTimeStampedDatae{true};
  IdGeneratorType _idGeneratorType{IdGeneratorType::Incremental};
};

} // namespace producer
} // namespace flex
