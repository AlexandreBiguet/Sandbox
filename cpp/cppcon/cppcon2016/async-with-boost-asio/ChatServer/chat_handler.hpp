/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   07 - Jul - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 08 - Jul - 2018
 */

#pragma once

#include <deque>
#include <istream>
#include <string>

#include "generic_server.hpp"

namespace Sandbox {

class chat_handler : public std::enable_shared_from_this<chat_handler> {
 public:
  chat_handler(boost::asio::io_service& service)
      : _service(service), _socket(service), _strand(service) {}

  boost::asio::ip::tcp::socket& socket() { return _socket; }

  void start() { read_packet(); }

  void send(const std::string& msg) {
    _service.post(_strand.wrap(
        [me = shared_from_this(), msg]() { me->queue_message(msg); }));
  }

 private:
  void queue_message(std::string msg) {
    // Call in stranded threads. So accessing the _send_packet_queue is ok
    // without lock
    bool write_in_progress = !_send_packet_queue.empty();
    _send_packet_queue.push_back(std::move(msg));
    if (!write_in_progress) {
      // Starting sending the packet if there is no other write in progress
      start_packet_send();
    }
  }

  void start_packet_send() {
    _send_packet_queue.front() += '\0';
    async_write(_socket, boost::asio::buffer(_send_packet_queue.front()),
                _strand.wrap([me = shared_from_this()](
                                 const boost::system::error_code& ec,
                                 std::size_t) { me->packet_send_done(ec); }));
  }

  void packet_send_done(const boost::system::error_code& error) {
    if (error) {
      return;
    }

    _send_packet_queue.pop_front();

    if (!_send_packet_queue.empty()) {
      start_packet_send();
    }
  }

  void read_packet() {
    boost::asio::async_read_until(
        _socket, _in_packet, '\0',
        [me = shared_from_this()](const boost::system::error_code& ec,
                                  std::size_t bytes_xfer) {
          me->read_packet_done(ec, bytes_xfer);
        });
  }

  void read_packet_done(const boost::system::error_code& error,
                        std::size_t bytes_transferred) {
    if (error) {
      return;
    }

    std::istream stream(&_in_packet);
    std::string packet_string;
    stream >> packet_string;

    read_packet();
  }

  boost::asio::io_service& _service;
  boost::asio::ip::tcp::socket _socket;
  boost::asio::io_service::strand _strand;
  boost::asio::streambuf _in_packet;
  std::deque<std::string> _send_packet_queue;
};

}  // namespace Sandbox
