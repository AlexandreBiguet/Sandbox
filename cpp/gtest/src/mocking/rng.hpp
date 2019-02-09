#pragma once

namespace mocking {

class Rng {
 public:
  virtual ~Rng() = default;
  virtual double generate(double min, double max) const = 0;
};

}  // namespace mocking
