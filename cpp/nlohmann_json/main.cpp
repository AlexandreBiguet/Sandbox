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

/**
 * Will it work to just json[] = "class -> std::vector".instance() ?
 * --> YEAH ! :-)
 */
template <typename T>
struct MyVector : public std::vector<T, std::allocator<T>> {
  using base_t = std::vector<T, std::allocator<T>>;
  MyVector() : base_t() {}
};

Two::Tensor3d<double> getTensor3d() {
  return {{{1.0, 2.0}, {3.0, 4.0}}, {{10.0, 20.0}, {30.0, 40.0}}};
}

/// Testing very simple set
void simpleTest1();

/// Testing if a non trivial tensor3d is appened properly
void simpleTest2();

/// Testing how to append quantities to an existing key
void simpleTest3();

int main() {
  simpleTest1();
  std::cout << std::endl;
  simpleTest2();
  std::cout << std::endl;
  simpleTest3();
  std::cout << std::endl;
  return 0;
}

void simpleTest3() {
  std::cout << "Simple Test 3 \n";
  nlohmann::json json, json_2;
  // json["list"] = {};
  json_2["a"] = 12.0;
  json_2["sublist 1"]["item 1"] = 1.0;
  json_2["sublist 1"]["item 2"] = 2.0;
  json_2["sublist 2"]["item 1"] = 10.0;
  json_2["sublist 2"]["item 2"] = 20.0;
  json["list"].push_back(json_2);
  std::cout << json << std::endl;
  std::cout << "Simple Test 3 : Ended\n";
}

void simpleTest2() {
  std::cout << "Simple Test 2 \n";
  nlohmann::json json;
  json["tensord3d"] = getTensor3d();
  std::cout << json << std::endl;
  std::cout << "Simple Test 2 : Ended \n";
}

void simpleTest1() {
  std::cout << "Simple Test 1 \n";
  nlohmann::json json;
  Two two;
  json["vector"] = two.vector();
  json["matrix"] = two.matrix();
  json["tensor3d"] = two.tensor3d();

  MyVector<double> vec;
  vec.push_back(1.0);
  vec.push_back(2.0);
  vec.push_back(3.0);
  json["myVector"] = vec;
  std::cout << json << std::endl;
  std::cout << "Simple Test 1 : Ended \n";
}
