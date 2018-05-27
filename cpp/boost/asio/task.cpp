//
//  task.cpp
//  Sandbox
//
//  Created by Alexandre Biguet on 23/04/2018 at 11:09.
//  Copyright © 2018 All rights reserved.
//

#include <iostream>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/signal_set.hpp>

#include <boost/log/trivial.hpp>

struct Task {
  Task(boost::asio::io_service& ioService, uint64_t timeout_ms = 1000)
      : _timer(ioService), _timeout_ms(timeout_ms), _isEnded(false) {}

  void clean() {
    _timer.cancel();
    _cb = nullptr;
  }

  boost::asio::deadline_timer _timer;
  uint64_t _timeout_ms;
  bool _isEnded;
  std::function<void(const boost::system::error_code&)> _cb;
};

int main() {
  std::cout << "boost asio io_service task binder \n";

  boost::asio::io_service ioService;

  boost::asio::signal_set signals(ioService, SIGINT, SIGTERM);

  signals.async_wait(
      [&](const boost::system::error_code&, int) { ioService.stop(); });

  std::shared_ptr<Task> taskPtr = std::make_shared<Task>(ioService);

  auto callback = [taskPtr](const boost::system::error_code&) {
    if (taskPtr->_isEnded) {
      return;
    }

    auto deadline = boost::asio::deadline_timer::traits_type::now() +
                    boost::posix_time::milliseconds(taskPtr->_timeout_ms);

    BOOST_LOG_TRIVIAL(trace) << "Coucou";

    taskPtr->_timer.expires_at(deadline);
    taskPtr->_timer.async_wait(taskPtr->_cb);
  };

  taskPtr->_cb = callback;
  taskPtr->_cb(boost::system::error_code());

  ioService.run();

  return 0;
}

// task.cpp ends here
