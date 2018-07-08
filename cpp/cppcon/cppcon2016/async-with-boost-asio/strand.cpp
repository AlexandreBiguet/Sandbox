#include <iostream>
#include <thread>

#include <boost/asio.hpp>

std::string get_current_date() {
  auto date =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  auto str_date(std::string(std::ctime(&date)));
  return str_date.substr(0, str_date.size() - 1);
}

void expired(const std::string& timer_name) {
  std::cout << "timer : " << timer_name << " : in  [" << get_current_date()
            << "] (thread id: " << std::this_thread::get_id() << ") \n";

  std::this_thread::sleep_for(std::chrono::seconds(3));

  std::cout << "timer : " << timer_name << " : out [" << get_current_date()
            << "] (thread id: " << std::this_thread::get_id() << ") \n";
}

int main() {
  boost::asio::io_service io;
  boost::asio::io_service::strand strand(io);

  boost::asio::deadline_timer t1(io, boost::posix_time::seconds(5));
  boost::asio::deadline_timer t2(io, boost::posix_time::seconds(5));

  // Adding a third timer which is not stranded.
  // It will wait on the time of one of the two created threads
  boost::asio::deadline_timer t3(io, boost::posix_time::seconds(7));

  t1.async_wait(strand.wrap([](auto... args) { expired("t1"); }));
  t2.async_wait(strand.wrap([](auto... args) { expired("t2"); }));

  t3.async_wait([](auto... args) { expired("t3"); });

  std::thread thread1([&io]() { io.run(); });
  std::thread thread2([&io]() { io.run(); });

  std::cout << "Waiting that the job is being done"
            << "(thread id : " << std::this_thread::get_id() << ") \n";

  thread1.join();
  thread2.join();

  std::cout << "Done \n";
  return 0;
}
