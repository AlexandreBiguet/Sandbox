#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/chrono.hpp>

std::string get_current_date() {
  auto date =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  return std::ctime(&date);
}

int main() {
  boost::asio::io_service service;

  boost::asio::deadline_timer timer(service, boost::posix_time::seconds(5));

  timer.async_wait([](auto... vn) {
    std::cout << "timer has timed-out : " << get_current_date() << std::endl;
  });

  std::cout << get_current_date() << "Before calling run function \n";

  service.run();

  std::cout << get_current_date() << "After the run has been performed \n";

  return 0;
}
