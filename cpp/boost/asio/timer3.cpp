/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   02 - Sep - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 02 - Sep - 2018
 */

// #include <functional>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

void print(const boost::system::error_code&, boost::asio::steady_timer* timer,
           int* count) {
  if (*count < 5) {
    std::cout << " -> " << *count << std::endl;
    ++(*count);
    timer->expires_at(timer->expiry() + boost::asio::chrono::seconds(1));
    timer->async_wait(
        boost::bind(print, boost::asio::placeholders::error, timer, count));
  }
}

int main() {
  boost::asio::io_context context;

  boost::asio::steady_timer timer(context, boost::asio::chrono::seconds(1));
  int thecount(0);

  timer.async_wait(
      std::bind(&print, boost::system::error_code(), &timer, &thecount));

  context.run();

  std::cout << "final count : " << thecount << std::endl;

  return 0;
}
