/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   21-Jun-2018
 * @Filename: main.cpp
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 21-Jun-2018
 */

#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>

/**
 * Testing how does nlohmann::json work
 * -> Fine and Easy :-)
 */

struct Two {
  template <typename T>
  using Matrix = std::vector<std::vector<T>>;

  template <typename T>
  using Tensor3d = std::vector<Matrix<T>>;

  double _a, _b;

  Two(double a = 0.0, double b = 1.0) : _a(a), _b(b) {}

  std::vector<double> vector() const { return {_a, _b}; }

  Matrix<double> matrix() const { return {vector()}; }

  Tensor3d<double> tensor3d() const { return {matrix()}; }
};

int main() {
  nlohmann::json json;
  Two two;
  json["vector"] = two.vector();
  json["matrix"] = two.matrix();
  json["tensor3d"] = two.tensor3d();
  std::cout << json << std::endl;
  return 0;
}
