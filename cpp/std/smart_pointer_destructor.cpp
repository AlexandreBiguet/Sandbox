#include <iostream>
#include <memory>

bool _global_nullptr_first = false;

class MyStruct {
 public:
  MyStruct(const std::string&& str) : _str(std::move(str)) {
    std::cout << "** " << _str << " : construction ** \n";
  }
  ~MyStruct() { std::cout << "** " << _str << " : destruction ** \n"; }

 private:
  std::string _str;
};

class Toto {
 public:
  Toto() : _struct(std::make_shared<MyStruct>("one")) {}

  void func() {
    if (_struct && _global_nullptr_first) {
      _struct = nullptr;
    }

    _struct = std::make_shared<MyStruct>("two");
  }

 private:
  std::shared_ptr<MyStruct> _struct;
};

int main() {
  Toto toto;
  toto.func();
  return 0;
}
