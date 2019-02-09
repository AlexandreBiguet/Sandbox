#include "coin_flipper.hpp"

#include <stdexcept>

namespace mocking {

CoinFlipper::CoinFlipper(Rng* rng) : _rng(rng) {
  if (!_rng) {
    throw std::invalid_argument("nullptr argument...");
  }
}

CoinFlipper::Result CoinFlipper::flip() const {
  return _rng->generate(0.0, 1.0) < 0.5 ? Result::Head : Result::Tail;
}

CoinFlipper2::CoinFlipper2(const std::shared_ptr<Rng>& rng) : _rng(rng) {
  if (!_rng) {
    throw std::invalid_argument("nullptr argument...");
  }
}

CoinFlipper2::Result CoinFlipper2::flip() const {
  return _rng->generate(0.0, 1.0) < 0.5 ? Result::Head : Result::Tail;
}

}  // namespace mocking
