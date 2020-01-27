//
//  gcd_euclid.cpp - interview_prep - Created by Alexandre BIGUET on 23/01/2020.
//

#include <iostream>

int gcd(int a, int b) {
  while (a > 0) {
    if (a < b) {
      std::swap(a, b);
    }
    a -= b;
  }
  return b;
}

int main() {
  std::cout << "testing gcd implem: \n"
            << "gcd(20, 30) : " << gcd(-20, -30) << "\n";
  return 0;
}
