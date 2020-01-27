//
//  queens_table.cpp - interview_prep - Created by Alexandre BIGUET on 25/01/2020.
//

#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>

namespace {

template <size_t N = 4>
class searching_queens {
 public:
  searching_queens() {
    for (size_t icol = 0; icol < _table_size; ++icol) {
      for (size_t jrow = 0; jrow < _table_size; ++jrow) {
        _queens[icol][jrow] = false;
      }
    }
  }

  void place_queens() {
    std::array<std::array<bool, N>, N> available;
    for (size_t icol = 0; icol < _table_size; ++icol) {
      for (size_t jrow = 0; jrow < _table_size; ++jrow) {
        available[icol][jrow] = true;
      }
    }

    // update_available(0, 0, available, false);
    place_queens_internal(0, 0, available);
  }

  void show_table() const {
    for (size_t icol = 0; icol < _table_size; ++icol) {
      for (size_t jrow = 0; jrow < _table_size; ++jrow) {
        std::cout <<  " | ";
        if (_queens[icol][jrow]) {
          std::cout  << 'Q';
        } else {
          std::cout << '-';
        }
      }

      std::cout <<" |" << std::endl;
    }
  }

 private:
  void place_queens_internal(size_t x, size_t y, std::array<std::array<bool, N>, N>& available) {
    if (y == _table_size) {
      return;
    }
    std::cout << " calling with [x : " << x << "] [y : " << y << "]\n";
    show(available);
    if (x == _table_size) {
      x = 0;
      update_available(x, y, available, true);
    }
    if (is_possible(x, y, available)) {
      _queens[x][y] = true;
      show_table();
      update_available(x, y, available, false);
      place_queens_internal(x, y + 1, available);
    } else {
      place_queens_internal(x + 1, y, available);
    }
  }

  bool is_possible(size_t x, size_t y, const std::array<std::array<bool, N>, N>& available) { return available[x][y]; }

  void update_available(size_t x, size_t y, std::array<std::array<bool, N>, N>& available, bool value) {
    for (size_t i = 0; i < _table_size; ++i) {
      available[x][i] = value;
      available[i][y] = value;
      available[x + i][y + i] = value;
      available[x - i][y - i] = value;
    }
  }

  void show(std::array<std::array<bool, N>, N>& available) {
    for (size_t icol = 0; icol < _table_size; ++icol) {
      for (size_t jrow = 0; jrow < _table_size; ++jrow) {
        std::cout <<  " | ";
        if (available[icol][jrow]) {
          std::cout  << '-';
        } else {
          std::cout << 'x';
        }
      }
      std::cout <<" |" << std::endl;
    }
    std::cout << std::endl;
  }

  size_t _table_size{N};
  std::array<std::array<bool, N>, N> _queens;
};

}  // namespace

int main() {
  searching_queens<> s;

  s.place_queens();
  // s.show_table();

  return EXIT_SUCCESS;
}
