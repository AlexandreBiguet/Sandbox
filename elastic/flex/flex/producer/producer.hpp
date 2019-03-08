#pragma once

#include "config.hpp"

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>

#include <flex/client/http.hpp>

namespace flex {
namespace producer {

class Producer {
public:
  Producer(boost::asio::io_context &context, const Config &config);

  /// \brief
  /// \tparam Functor a callable with signature nlohmann::json(void)
  /// \param functor
  template <typename Functor> void run(const Functor &&functor) {

    // clang-format off
    boost::asio::spawn(
        _strand, [this, functor](boost::asio::yield_context yield) {
          boost::system::error_code ec;
          _client.connect(yield[ec]);

          while (loop(yield)) {
            _client.post(_config._target, functor(), yield[ec]);
            if (ec) {
              throw std::runtime_error("post : " + ec.message());
            }
          }
        });
    // clang-format on
  }

private:

  bool loop(boost::asio::yield_context yield);

  boost::asio::io_context::strand _strand;
  Config _config;
  boost::asio::deadline_timer _timer;
  client::Http _client;
};

} // namespace producer
} // namespace flex
