//
//  main.cpp - interview_prep - Created by Alexandre BIGUET on 27/01/2020.
//

#include <array>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <vector>

class range {
 public:
  range() = default;

  explicit range(const std::string& str) { set(str); }

  void set(const std::string& str) {
    std::stringstream stream{str};
    std::string tmp;
    std::array<double, 2> values{0, 0};
    size_t count{0};
    bool okline{false};
    while (getline(stream, tmp, ' ')) {
      okline = true;
      try {
        values[count++] = std::strtod(tmp.c_str(), nullptr);
      } catch (...) {
        throw std::invalid_argument("input string is expected to be of the form: X WHITESPACE Y");
      }
    }

    if (!okline) {
      throw std::invalid_argument("invalid input range");
    }

    _range.first = values[0];
    _range.second = values[1];
  }

  double low() const { return _range.first; }

  double high() const { return _range.second; }

  std::string to_string() const {
    std::stringstream stream;
    stream << " [ " << low() << " ; " << high() << " ]";
    return stream.str();
  }

 private:
  std::pair<double, double> _range;
};

class ranges_db {
 public:
  explicit ranges_db(const std::string& path_to_file) {
    init_map_implem(path_to_file);
    // init_vec_impl(path_to_file);
  }

  std::string to_string() const {
    std::stringstream stream;
    stream << "Input ranges : \n";
    for (const auto& p : _input_ranges) {
      stream << p.first << "   -->   " << p.second << std::endl;
    }
    return stream.str();
  }

  size_t query_count_arith(double value) {
    double min_value = std::begin(_input_ranges)->first;
    double max_value = (--std::end(_input_ranges))->first;

    std::cout << "(min : max) ranges values : ( " << min_value << " : " << max_value << " ) \n";

    if (value < min_value || value > max_value) {
      std::cout << " (value: " << value << ") is out of range \n";
      return 0;
    }

    auto it = _input_ranges.find(value);
    if (it != std::end(_input_ranges)) {
      std::cout << "(value : " << value << ") is a key in the map \n";
      if (it != std::begin(_input_ranges)) {
        --it;
      }
    } else {
      std::cout << "(value : " << value
                << ") is a not key in the map -> looking for floored value: " << std::floor(value) << std::endl;
      it = _input_ranges.find(std::floor(value));
      if (it == std::end(_input_ranges)) {
        throw std::runtime_error("internal error: corresponding value should have been found");
      }
    }

    if (it->second < 0) {
      throw std::runtime_error("internal error. counting has negative value which should not happen");
    }

    return it->second;
  }

  size_t query_count(double value) {
    double min_value = std::begin(_input_ranges)->first;
    double max_value = (--std::end(_input_ranges))->first;

    if (value < min_value || value > max_value) {
      // std::cout << " (value: " << value << ") is out of range \n";
      return 0;
    }

    auto lower = _input_ranges.lower_bound(value);
    if (value != lower->first) {
      --lower;
    }
    // std::cout << " [ key : value ] : [" << lower->first << " : " << lower->second << "] \n";
    return lower->second;
  }

 private:
  void init_map_implem(const std::string& path_to_file) {
    std::ifstream stream{path_to_file};
    std::string line;
    while (std::getline(stream, line)) {
      range rn;
      try {
        rn.set(line);
      } catch (...) {
        break;
      }

      auto pair = _input_ranges.insert({rn.low(), +1});

      if (!pair.second) {
        _input_ranges[rn.low()]++;
      }

      pair = _input_ranges.insert({rn.high(), -1});

      if (!pair.second) {
        _input_ranges[rn.high()]--;
      }
    }

    std::vector<int> partial_count;

    partial_count.reserve(_input_ranges.size());
    for (const auto& p : _input_ranges) {
      partial_count.push_back(p.second);
    }

    std::partial_sum(std::begin(partial_count), std::end(partial_count), std::begin(partial_count));

    std::size_t index{0};
    for (auto& p : _input_ranges) {
      p.second = partial_count[index++];
    }
  }

  std::map<double, int> _input_ranges;
};

void simple_test() {
  std::string path{"/Users/alexandrebiguet/Home/Programs/Alex/Sandbox/prep/tall_ranges/inputs/input_ranges.txt"};
  ranges_db db(path);

  std::cout << db.to_string() << std::endl;

  std::vector<double> queries{0.0, 12.0, 12.5, 14, 16.5, 19.0, 20.0, 21.0};

  for (const auto& q : queries) {
    std::cout << "Query (" << q << ") : " << db.query_count(q) << std::endl;
  }
}

int main(int argc, char** argv) {
  // first argument is the path to the range files

  if (argc != 2) {
    std::cout << "ranges : USAGE \n"
              << "   range path_to_file \n\n"
              << "where 'path_to_file' is the path to the ranges file\n";
    return EXIT_FAILURE;
  }

  std::string path{argv[1]};
  ranges_db db(path);

  while (true) {

    std::string tmp;
    std::cin >> tmp;
    if (std::isalpha(tmp[0])) {
      std::cout << " stopping \n";
      break;
    }

    double value = std::strtod(tmp.c_str(), nullptr);

    std::cout << db.query_count(value) << std::endl;
  }


  return EXIT_SUCCESS;
}