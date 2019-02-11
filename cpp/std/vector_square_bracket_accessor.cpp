#include <iostream>
#include <vector>

static size_t g_instance_number{0};

class Obj {
 public:
  explicit Obj(int a) : _a(g_instance_number) {
    std::cout << "constructed [" << g_instance_number << "]\n";
    ++g_instance_number;
  }
  Obj(const Obj& obj) : _a(obj.a()) { std::cout << "copied [" << _a << "]\n"; }
  int a() const { return _a; }

 private:
  int _a;
};

int main() {
  std::vector<Obj> vec{Obj(1), Obj(2), Obj(3)};

  std::cout << "\n -- \n";
  Obj o = vec[0];

  std::cout << "\n -- \n";
  Obj& o_ref = vec[0];

  return 0;
}
