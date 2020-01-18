#include <cstdlib>
#include <iostream>
#include <string>
#include <bitset>
#include <type_traits>

// SFINAE for safety. Sue me for putting it in a macro for brevity on the function
#define IS_INTEGRAL(T) typename std::enable_if< std::is_integral<T>::value >::type* = 0

template<class T>
std::string integral_to_binary_string(T byte, IS_INTEGRAL(T))
{
  std::bitset<sizeof(T)> bs(byte);
  return bs.to_string();
}

int main(){
  int a = 50;
  std::cout << integral_to_binary_string(a) << std::endl;

  std::bitset<sizeof(int)> bs(a);
  std::cout << (~bs).to_ulong();

}

/*
int main() {
  std::cout << std::is_same<int, std::int32_t>::value << '\n';
  std::cout << std::is_same<int, int>::value << '\n';
  std::cout << std::is_same<int, double>::value << '\n';
  std::cout << std::is_same<int, int &>::value << '\n';

  std::cout << std::endl;
  std::cout << sizeof(A) << "\n";

  return EXIT_SUCCESS;
}
*/