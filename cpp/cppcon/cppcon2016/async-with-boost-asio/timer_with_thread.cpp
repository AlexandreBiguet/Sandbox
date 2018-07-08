#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>

#include <boost/asio.hpp>

/// Two versions:
/// 1- one thread
/// 2- two threads : Off course garbage output

enum class Version { One, Two };

static Version version_switch = Version::One;

std::string get_current_date() {
  auto date =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  auto str_date(std::string(std::ctime(&date)));
  return str_date.substr(0, str_date.size() - 1);
}

void expired(const std::string& timer_name) {
  std::cout << "timer : " << timer_name << " : in  [" << get_current_date()
            << "] \n";

  std::this_thread::sleep_for(std::chrono::seconds(3));

  std::cout << "timer : " << timer_name << " : out [" << get_current_date()
            << "] \n";
}

void one_thread_version() {
  boost::asio::io_service ioService;
  boost::asio::deadline_timer t1(ioService, boost::posix_time::seconds(5));
  boost::asio::deadline_timer t2(ioService, boost::posix_time::seconds(5));

  t1.async_wait([](auto... vn) { expired("t1"); });
  t2.async_wait([](auto... vn) { expired("t2"); });

  std::thread myThread([&t1, &t2, &ioService]() { ioService.run(); });

  std::cout << "Blocking while the thread finishes its job ["
            << get_current_date() << "] \n\n";

  myThread.join();

  std::cout << "All right " << get_current_date() << std::endl;
}

void two_thread_version() {
  boost::asio::io_service ioService;
  boost::asio::deadline_timer t1(ioService, boost::posix_time::seconds(5));
  boost::asio::deadline_timer t2(ioService, boost::posix_time::seconds(5));

  t1.async_wait([](auto... vn) { expired("t1"); });
  t2.async_wait([](auto... vn) { expired("t2"); });

  std::thread thread1([&ioService]() { ioService.run(); });
  std::thread thread2([&ioService]() { ioService.run(); });

  std::cout << "Blocking while the thread finishes its job ["
            << get_current_date() << "] \n\n";

  thread1.join();
  thread2.join();

  std::cout << "All right " << get_current_date() << std::endl;
}

int main(int argc, char** argv) {
  if (argc > 1) {
    std::string posarg(argv[1]);
    std::transform(posarg.begin(), posarg.end(), posarg.begin(), ::tolower);
    if (posarg == "one") {
      version_switch = Version::One;
    } else if (posarg == "two") {
      version_switch = Version::Two;
    } else {
      std::cout << " You can choose between one or two as 1st positional arg. "
                   "Default is one\n";
    }
  }

  if (version_switch == Version::One) {
    std::cout << "One thread version \n\n";
    one_thread_version();
  } else {
    std::cout << "Two threads version \n\n";
    two_thread_version();
  }

  return 0;
}
