//
//  main.cpp
//  Codingame
//
//  Created by Alexandre Biguet on 19/09/2018 at 08:31.
//

#include "t1.hpp"
#include "t2.hpp"
int main(int argc, char** argv) {
  int N = 10000;

  if (argc > 1) {
    N = std::atoi(argv[1]);
  }

  for (int i = 0; i < N; ++i) {
    std::cout << Algorithm::getPositionAt(i) << '\n';
  }

  return 0;
}

// main.cpp ends here
