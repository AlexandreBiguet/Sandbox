/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   02 - Sep - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 03 - Sep - 2018
 */

/// This is the boost 1.68 equivalent to the task.cpp

#include <iostream>

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

struct Task {
  Task(boost::asio::io_context& context, uint64_t timeout_ms = 500)
      : _timer(context), _timeout_ms(timeout_ms) {}

  boost::asio::deadline_timer _timer;
  uint64_t _timeout_ms;
  std::function<void(const boost::system::error_code&)> _callback;
};

int main() {
  boost::asio::io_context context;
  boost::asio::signal_set signals(context, SIGINT, SIGTERM);
  signals.async_wait([&context](const boost::system::error_code&, int) {
    std::cout << "good bye";
    context.stop();
  });

  std::shared_ptr<Task> taskPtr = std::make_shared<Task>(context);

  auto cb = [t = taskPtr](const boost::system::error_code&) {
    auto deadline = boost::asio::deadline_timer::traits_type::now() +
                    boost::posix_time::milliseconds(t->_timeout_ms);

    BOOST_LOG_TRIVIAL(trace) << "Coucou";

    t->_timer.expires_at(deadline);
    t->_timer.async_wait(t->_callback);
  };
  taskPtr->_callback = cb;
  taskPtr->_callback(boost::system::error_code());

  context.run();

  return 0;
}
