

#include <iostream>
#include <string>
#include <vector>

enum class princess_position_t { bottom_left, bottom_right, top_right, top_left };

princess_position_t princess_position(int n, const std::vector<std::string>& grid) {
  if (grid[0][0] == 'p') {
    return princess_position_t::top_left;
  } else if (grid[0][n - 1] == 'p') {
    return princess_position_t::top_right;
  } else if (grid[n - 1][0] == 'p') {
    return princess_position_t::bottom_left;
  } else {
    return princess_position_t::bottom_right;
  }
}

void displayPathtoPrincess(int n, vector<string> grid) {
  int count = (n - 1) / 2;  // n is odd by def
  auto pos = princess_position(n, grid);
  if (princess_position_t::bottom_left == pos || princess_position_t::bottom_right == pos) {
    for (int i = 0; i < count; ++i) {
      std::cout << "DOWN\n";
    }
    if (princess_position_t::bottom_left == pos) {
      for (int i = 0; i < count; ++i) {
        std::cout << "LEFT\n";
      }
    } else {
      for (int i = 0; i < count; ++i) {
        std::cout << "RIGHT\n";
      }
    }
  } else {
    for (int i = 0; i < count; ++i) {
      std::cout << "UP\n";
    }
    if (princess_position_t::top_left == pos) {
      for (int i = 0; i < count; ++i) {
        std::cout << "LEFT\n";
      }
    } else {
      for (int i = 0; i < count; ++i) {
        std::cout << "RIGHT\n";
      }
    }
  }
}

int main() {
  // TODO
}