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
  Rng* _rng;
};

class CoinFlipper2 {
 public:
  enum Result { Head = 0, Tail = 1 };

  CoinFlipper2(const std::shared_ptr<Rng>& rng);
  Result flip() const;

 private:
  std::shared_ptr<Rng> _rng;
};

}  // namespace mocking
