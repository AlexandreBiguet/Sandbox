/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   02 - Sep - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 02 - Sep - 2018
 */

#include <chrono>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Printer {
 public:
  Printer(boost::asio::io_context& context, int timeout_s = 1)
      : _timeout_s(timeout_s), _timer(context, _timeout_s), _count(0) {
    _timer.async_wait(boost::bind(&Printer::print, this));
  }

  ~Printer() { std::cout << "final count : " << _count << "\n"; }

 private:
  void print() {
    if (_count < 5) {
      std::time_t t = std::chrono::system_clock::to_time_t(
          std::chrono::system_clock::now());
      std::cout << std::ctime(&t);

      ++_count;
      _timer.expires_at(_timer.expiry() + _timeout_s);
      _timer.async_wait(boost::bind(&Printer::print, this));
    }
  }

  boost::asio::chrono::seconds _timeout_s;
  boost::asio::steady_timer _timer;
  int _count;
};

int main() {
  boost::asio::io_context context;

  Printer printer(context);

  context.run();

  return 0;
}
