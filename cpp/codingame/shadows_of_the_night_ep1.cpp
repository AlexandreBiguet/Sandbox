#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class Direction { DL, DR, UL, UR, R, L, D, U };

#define TRIGGER_CACHE_VALUE 2

class Position {
public:
  Position() = default;
  Position(int x, int y) : _x(x), _y(y) {}
  int x() const { return _x; }
  int y() const { return _y; }
  void x(int x) { _x = x; }
  void y(int y) { _y = y; }
  std::string toString() const {
    return {std::to_string(_x) + " " + std::to_string(_y)};
  }

private:
  int _x, _y;
};

static int middle(int a, int b, const Direction& dir) {
  int s = a + b;

  if (s % 2 == 0) {
    return s / 2;
  }

  if (dir == Direction::L || dir == Direction::U) {
    return static_cast<int>(std::floor(s/2.));
  }

  return static_cast<int>(std::ceil(s/2.));
}

class BatController {
public:
  /// \brief
  /// \param x0
  /// \param y0
  /// \param nw
  /// \param nh
  BatController(int x0, int y0, int nw, int nh)
      : _cur(x0, y0), _prev(x0, y0), _nw(nw), _nh(nh),  _min(0, 0),
        _max(nw - 1, nh - 1), _cache(std::make_pair(Direction::U, 0)) {}

  /// \brief
  /// \param dir
  /// \return
  std::string next(const Direction &dir) {

    update_cache(dir);
    std::cerr << "  --> " << _cache.second << '\n';

    _prev = _cur;
    _cur = advance(dir);

//    if (check_cache()) {
//      // Advance twice
//      _prev = _cur;
//      _cur = advance(dir);
//    }

    return _cur.toString();
  }

private:

  Position advance(const Direction& dir) {

    Position next_pos;
    if (dir == Direction::D) {
      next_pos.y(middle_down());
      next_pos.x(_cur.x());
    } else if (dir == Direction::U) {
      next_pos.y(middle_up());
      next_pos.x(_cur.x());
    } else if (dir == Direction::L) {
      next_pos.x(middle_left());
      next_pos.y(_cur.y());
    } else if (dir == Direction::R) {
      next_pos.x(middle_right());
      next_pos.y(_cur.y());
    } else if (dir == Direction::DL) {
      next_pos.x(middle_left());
      next_pos.y(middle_down());
    } else if (dir == Direction::DR) {
      next_pos.x(middle_right());
      next_pos.y(middle_down());
    } else if (dir == Direction::UL) {
      next_pos.x(middle_left());
      next_pos.y(middle_up());
    } else if (dir == Direction::UR) {
      next_pos.x(middle_right());
      next_pos.y(middle_up());
    } else {
      throw std::runtime_error(
          "Use std::map<Direction, std::function> instead of this ugly stuff");
    }
    return next_pos;
  }

  int middle_up() {
    int ymax = _cur.y();
    _max.y(ymax);
    int ylow = _min.y();

    if (_prev.y() < _cur.y() && _prev.y() > ylow) {
      ylow = _prev.y();
    }

    return middle(ylow, ymax, Direction::U);
  }

  int middle_down() {
    int ylow = _cur.y();
    _min.y(ylow);
    int ymax = _max.y();

    if (_prev.y() > _cur.y() && _prev.y() < ymax) {
      ymax = _prev.y();
    }

    return middle(ylow, ymax, Direction::D);
  }

  int middle_left() {
    int xmax = _cur.x();
    _max.x(xmax);
    int xlow = _min.x();

    if (_prev.x() > xlow && _prev.x() < _cur.x()) {
      xlow = _prev.x();
    }

    return middle(xlow, xmax, Direction::L);
  }

  int middle_right() {
    int xlow = _cur.x();
    _min.x(xlow);
    int xmax = _max.x();

    if (_prev.x() > _cur.x() && _prev.x() < xmax) {
      xmax = _prev.x();
    }

    return middle(xlow, xmax, Direction::R);
  }

  void update_cache(const Direction &dir) {
    if (_cache.first == dir) {
      ++_cache.second;
    } else {
      _cache.first = dir;
      _cache.second = 1;
    }
  }

  bool check_cache(int trigger_value = 2) {
    return (_cache.second >= trigger_value);
  }

  Position _cur;
  Position _prev;
  int _nw, _nh;
  Position _min;
  Position _max;
  std::pair<Direction, int> _cache;
};

static const std::map<std::string, Direction> _dirString{
    {"D", Direction::D},   {"DL", Direction::DL}, {"DR", Direction::DR},
    {"L", Direction::L},   {"R", Direction::R},   {"U", Direction::U},
    {"UL", Direction::UL}, {"UR", Direction::UR}};

static Direction direction_from_string(const std::string &dir) {
  return _dirString.at(dir);
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main() {
  int W; // width of the building.
  int H; // height of the building.
  cin >> W >> H;
  cin.ignore();
  int N; // maximum number of turns before game over.
  cin >> N;
  cin.ignore();
  int X0; // Batman position
  int Y0;
  cin >> X0 >> Y0;
  cin.ignore();

  BatController batman(X0, Y0, W, H);

  // game loop
  while (1) {

    string bombDir; // the direction of the bombs from batman's current
    // location (U, UR, R, DR, D, DL, L or UL)
    cin >> bombDir;
    cin.ignore();

    std::cerr << "Direction : " << bombDir << '\n';
    std::cout << batman.next(direction_from_string(bombDir)) << std::endl;

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    // the location of the next window Batman should jump to.
  }
}
