#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor
 *seems not follow your orders.
 **/
int main() {
  int lightX;     // the X position of the light of power
  int lightY;     // the Y position of the light of power
  int initialTX;  // Thor's starting X position
  int initialTY;  // Thor's starting Y position
  cin >> lightX >> lightY >> initialTX >> initialTY;
  cin.ignore();

  // game loop
  while (1) {
    int remainingTurns;  // The remaining amount of turns Thor can move. Do not
                         // remove this line.
    cin >> remainingTurns;
    cin.ignore();

    int iy = lightY - initialTY;
    int ix = lightX - initialTX;
    std::string direction;

    if (iy == 0) {
      if (ix > 0) {
        direction = "E";
        ++initialTX;
      } else {
        direction = "W";
        --initialTX;
      }
    } else if (ix == 0) {
      if (iy < 0) {
        direction = "N";
        --initialTY;
      } else {
        direction = "S";
        ++initialTY;
      }
    } else {
      auto delta_y = static_cast<double>(-iy);
      auto delta_x = static_cast<double>(ix);
      // auto slope = delta_y / delta_x;

      auto theta = std::atan2(delta_y, delta_x);
      if (theta > 0. && theta < M_PI / 2.0) {
        direction = "NE";
        ++initialTX;
        --initialTY;
      } else if (theta > M_PI / 2.0 && theta < M_PI) {
        direction = "NW";
        --initialTX;
        --initialTY;
      } else if (theta < 0.0 && theta > -M_PI / 2.) {
        direction = "SE";
        ++initialTX;
        ++initialTY;
      } else {
        direction = "SW";
        --initialTX;
        ++initialTY;
      }
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    // A single line providing the move to be made: N NE E SE S SW W or NW
    cout << direction << endl;
  }
}
