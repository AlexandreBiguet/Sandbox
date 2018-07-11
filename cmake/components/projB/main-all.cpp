/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   11 - Jul - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 11 - Jul - 2018
 */

#include <iostream>

#include <projA/Hello/Hello.hpp>
#include <projA/Hi/Hi.hpp>

int main() {
  std::cout << "Saying Hello \n";
  projA::print();

  std::cout << "Saying Hi \n";
  projA::hi();

  return 0;
}
