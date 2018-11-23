#include <ctpl.h>

#include <iostream>
#include <thread>

class Some {
 public:
  Some() = default;

  void init(size_t n) {
    _lol = 0;
    for (size_t i = 0; i < n; ++i) {
      _lol += i;
    }
    std::cout << "the end from : " << _lol << " " << std::this_thread::get_id()
              << std::endl;
  }

  size_t lol() const { return _lol; }

 private:
  size_t _lol{0};
};

class Hum {
 public:
  Hum() : _pool(1) {}
  void start(size_t n) {
    _pool.push([&n, this](int) { _some.init(n); });
  }

  void get(const std::function<void(size_t)>& handler) {
    _pool.push([this, handler](int) { handler(_some.lol()); });
  }

 private:
  ctpl::thread_pool _pool;
  Some _some;
};

int main() {
  Hum h;
  h.start(1000);
  std::cout << "coucou from : " << std::this_thread::get_id() << std::endl;
  h.get([](size_t a) { std::cout << " a = " << a << std::endl; });
  return 0;
}
