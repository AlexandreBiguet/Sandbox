//
//
//

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include <boost/log/trivial.hpp>

#include <flex/algo/algo.hpp>

int main(int argc, char **argv) {
  std::size_t size{20000};

  if (argc == 2) {
    size = std::strtoul(argv[1], nullptr, 0);
  }

  std::vector<double> vec(size);

  std::random_device rd{};
  std::mt19937 gen{rd()};

  double expected_mean{10.0};
  double expected_stddev{2.0};

  std::normal_distribution<double> distribution{expected_mean, expected_stddev};

  std::generate(std::begin(vec), std::end(vec),
                [&distribution, &gen]() { return distribution(gen); });

  auto scores = flex::algo::zscore(std::begin(vec), std::end(vec));

  std::map<std::string, std::size_t> results{
      {"fatal", 0}, {"error", 0}, {"warning", 0}};

  std::for_each(std::begin(scores), std::end(scores), [&results](auto &v) {
    if (v > 4.5) {
      BOOST_LOG_TRIVIAL(fatal) << v;
      ++results.at("fatal");
    } else if (v > 3.0) {
      BOOST_LOG_TRIVIAL(error) << v;
      ++results.at("error");
    } else if (v > 2.0) {
      BOOST_LOG_TRIVIAL(warning) << v;
      ++results.at("warning");
    }
  });

  std::cout << "\n - Overview : \n";
  printf("%-15s %-15s %-15s \n", "type", "count", "ratio");
  for (size_t i = 0; i < (3 * 15 + 2); ++i) {
    std::cout << "-";
  }
  std::cout << std::endl;
  for (const auto &elements : results) {
    printf("%-15s %-15zu %-15.5f \n", elements.first.c_str(), elements.second,
           elements.second / static_cast<double>(size));
  }

  return 0;
}
