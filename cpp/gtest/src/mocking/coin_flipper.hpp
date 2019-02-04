#pragma once

#include "rng.hpp"

#include <memory>

namespace mocking {

class CoinFlipper {
 public:
  enum Result { Head = 0, Tail = 1 };

  CoinFlipper(Rng* rng);
  Result flip() const;

 private:
  std::shared_ptr<Rng> _rng;
};

}  // namespace mocking
