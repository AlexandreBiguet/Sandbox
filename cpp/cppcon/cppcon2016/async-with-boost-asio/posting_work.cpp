#include <iostream>
#include <thread>

#include <boost/asio.hpp>

int main() {
  boost::asio::io_service ioService;
  ioService.post([]() { std::cout << "my name is Bond\n"; });
  ioService.post([]() { std::cout << "James\n"; });
  ioService.post([]() { std::cout << "Bond\n"; });

  // Off course it is possible to run the io service from the main thread
  // ioService.run();

  std::thread thread([&ioService]() { ioService.run(); });

  std::cout << "blocking while the created threads has job to do \n";
  thread.join();
  std::cout << "job done \n";
  return 0;
}
