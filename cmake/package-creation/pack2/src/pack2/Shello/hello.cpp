#include "hello.hpp"

#include <iostream>

#include <Hello/hello.hpp>

namespace pack2 {
namespace Shello {
void hello() {
  std::cout << "This is the HelloProject hello function : \n";
  Test::hello();
}

}  // namespace Shello
}  // namespace pack2
