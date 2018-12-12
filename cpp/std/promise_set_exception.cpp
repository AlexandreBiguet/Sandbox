#include <future>
#include <iostream>
#include <thread>

// #define FUNC_RETURN_TRUE

bool func() {
#ifdef FUNC_RETURN_TRUE
  return true;
#else
  return false;
#endif
}

int main() {
  std::promise<void> promise;

  std::thread t([&promise] {
    if (func()) {
      promise.set_exception(
          std::make_exception_ptr(std::runtime_error("error")));
    } else {
      promise.set_value();
    }
  });

  try {
    promise.get_future().get();
  } catch (const std::exception& e) {
    std::cout << "Exception from the thread: " << e.what() << '\n';
  }

  t.join();

  return 0;
}
