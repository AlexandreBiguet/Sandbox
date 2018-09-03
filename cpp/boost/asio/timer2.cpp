/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   02 - Sep - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 02 - Sep - 2018
 */

#include <iostream>

#include <boost/asio.hpp>

/// Async wait of default_timeout seconds
int main() {
  const int default_timeout = 3;

  boost::asio::io_context context;

  boost::asio::steady_timer timer(
      context, boost::asio::chrono::seconds(default_timeout));

  timer.async_wait([&default_timeout](const boost::system::error_code&) {
    std::cout << "Callback called after " << default_timeout << " seconds \n";
  });

  context.run();

  return 0;
}
