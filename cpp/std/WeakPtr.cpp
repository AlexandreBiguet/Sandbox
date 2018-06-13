/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   13 - Jun - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#include <iostream>
#include <memory>

class Test {
 private:
  double _a;

 public:
  explicit Test(double a) : _a(a) {}

  void print() { std::cout << "a = " << _a << std::endl; }
};

int main() {
  /**
   * This should print 10.0 only once
   * */

  std::weak_ptr<Test> wPtr;

  {
    std::shared_ptr<Test> sPtr(std::make_shared<Test>(10.0));

    wPtr = sPtr;

    if (auto p = wPtr.lock()) {
      p->print();
    }
  }

  if (auto p = wPtr.lock()) {
    p->print();
  }

  return 0;
}
