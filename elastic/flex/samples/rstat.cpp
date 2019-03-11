//
//
//

#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include <flex/algo/stat.hpp>

namespace {

void print(const flex::algo::RStat &stat) {
  std::cout << std::endl;
  std::cout << "min value : " << stat.min() << "\n";
  std::cout << "max value : " << stat.max() << "\n";
  std::cout << "mean      : " << stat.mean() << "\n";
  std::cout << "variance  : " << stat.variance() << "\n";
  std::cout << "stddev    : " << stat.stddev() << "\n";
  std::cout << "rms       : " << stat.rms() << "\n";
  std::cout << "skew      : " << stat.skew() << "\n";
  std::cout << "kurt      : " << stat.kurt() << "\n";
}

} // namespace

int main() {

  const std::size_t size{20};
  std::vector<double> vec;
  vec.resize(size);
  flex::algo::RStat stat;

  {
    std::iota(std::begin(vec), std::end(vec), 0.);

    std::for_each(std::begin(vec), std::end(vec),
                  [](const auto &e) { std::cout << e << " "; });

    stat.push(std::begin(vec), std::end(vec));

    print(stat);
  }

  {
    std::cout << "\n\n --- random number \n";

    std::random_device rd{};
    std::mt19937 gen{rd()};

    double expected_mean{10.0};
    double expected_stddev{2.0};

    std::normal_distribution<double> distribution{expected_mean,
                                                  expected_stddev};
    std::generate(std::begin(vec), std::end(vec),
                  [&distribution, &gen]() { return distribution(gen); });

    stat.clear();

    std::for_each(std::begin(vec), std::end(vec), [&stat](const auto &e) {
      std::cout << e << " ";
      stat.push(e);
    });

    print(stat);

    std::cout << "\nexpected mean   : " << expected_mean << "\n";
    std::cout << "expected stddev : " << expected_stddev << "\n";
    std::cout << " 1/ sqrt(size) = " << 1.0 / std::sqrt(size) << std::endl;
    std::cout << " stddev / sqrt(size) = " << stat.stddev() / std::sqrt(size)
              << std::endl;
  }

  return 0;
}