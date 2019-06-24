#pragma once

#include <string>
#include <vector>

namespace attparse {

struct Input {
  Input() = default;
  std::vector<std::string> _lines;
  std::vector<std::string> _queries;
};

}  // namespace attparse