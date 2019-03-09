//
//
//

#pragma once

#include "config.hpp"

#include <memory>

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

    boost::asio::spawn( // trick clang-format :-)
        _strand.get_io_context(),
        [this, functor](boost::asio::yield_context yield) {
          boost::system::error_code ec;
          _client.connect(yield);

          if (_config._requireTimeStampedDatae) {
            timestamp(yield);
          }

          while (loop(yield[ec])) {
            _client.post(_config._index + "/_doc/" + generateDocumentId(),
                         functor(), yield[ec]);
            if (ec) {
              throw std::runtime_error("post : " + ec.message());
            }
          }
        });
  }

private:
  bool loop(boost::asio::yield_context yield);
  void timestamp(boost::asio::yield_context yield);
  std::string generateDocumentId() const;

  boost::asio::io_context::strand _strand;
  Config _config;
  boost::asio::deadline_timer _timer;
  client::Http _client;
};

} // namespace producer
} // namespace flex
