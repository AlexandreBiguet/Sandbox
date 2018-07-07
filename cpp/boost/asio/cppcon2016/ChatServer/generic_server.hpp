/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   07 - Jul - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 08 - Jul - 2018
 */
#pragma once

#include <memory>
#include <thread>

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

namespace Sandbox {

template <typename ConnectionHandler>
class asio_generic_server {
  using shared_handler_t = std::shared_ptr<ConnectionHandler>;

 public:
  asio_generic_server(size_t thread_count = 1)
      : _thread_count(thread_count), _acceptor(_io_service) {}

  void start_server(uint16_t port) {

    auto handler = std::make_shared<ConnectionHandler>(_io_service);

    // setting up the tcp connection acceptor
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();

    // The handler is captured by value
    _acceptor.async_accept(handler->socket(), [this, handler](auto ec) {
      handle_new_connection(handler, ec);
    });

    // Starting the thread pool to process the asio event
    for (size_t i = 0; i < _thread_count; ++i) {
      _thread_pool.emplace_back([this]() { _io_service.run(); });
    }
  }

 private:
  /// This hanlder is called whenever a new connection comes in
  void handle_new_connection(shared_handler_t handler,
                             const boost::system::error_code& error) {
    if (error) {
      return;
    }

    handler->start();
    auto another_handler = std::make_shared<ConnectionHandler>(_io_service);
    _acceptor.async_accept(another_handler->socket(),
                           [this, another_handler](auto ec) {
                             handle_new_connection(another_handler, ec);
                           });
  }

  size_t _thread_count;
  std::vector<std::thread> _thread_pool;
  boost::asio::io_service _io_service;
  boost::asio::ip::tcp::acceptor _acceptor;
};

}  // namespace Sandbox
