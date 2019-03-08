//
//
//

#include "http.hpp"

#include <memory>

#include <boost/asio/connect.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/version.hpp>
#include <boost/log/trivial.hpp>

#include <nlohmann/json.hpp>

namespace flex {
namespace client {

// ----------------------------------------------------------------------------

Http::Config::Config(std::string &&host, std::string &&port)
    : _host(std::move(host)), _port(std::move(port)) {}

// ----------------------------------------------------------------------------

Http::Config Http::Config::createDefault() {
  return Config("localhost", "9200");
}

// ----------------------------------------------------------------------------

Http::Http(boost::asio::io_context &context, const Http::Config &config)
    : _config(config), _resolver(context), _socket(context) {}

// ----------------------------------------------------------------------------

void Http::connect(boost::asio::yield_context yield) {
  boost::system::error_code ec;

  auto const results =
      _resolver.async_resolve(_config._host, _config._port, yield[ec]);

  if (ec) {
    throw std::runtime_error("resolve : " + ec.message());
  }

  boost::asio::async_connect(_socket, results.begin(), results.end(),
                             yield[ec]);

  if (ec) {
    throw std::runtime_error("connect : " + ec.message());
  }
}

// ----------------------------------------------------------------------------

Http::Response Http::get(const std::string &target,
                         boost::asio::yield_context yield) {

  boost::system::error_code ec;

  Request req{boost::beast::http::verb::get, target, _http_version};
  req.set(boost::beast::http::field::host, _config._host);
  req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  // Send the HTTP request to the remote host
  boost::beast::http::async_write(_socket, req, yield[ec]);

  if (ec) {
    throw std::runtime_error("write : " + ec.message());
  }

  // Declare a container to hold the response
  Response res;

  boost::beast::http::async_read(_socket, _buffer, res, yield[ec]);

  if (ec) {
    throw std::runtime_error("read : " + ec.message());
  }

  return res;
}

// ----------------------------------------------------------------------------

Http::Response Http::write(boost::beast::http::verb verb,
                           const std::string &target, const std::string &body,
                           boost::asio::yield_context yield) {
  boost::system::error_code ec;

  Request req{verb, target, _http_version};
  req.set(boost::beast::http::field::host, _config._host);
  req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(boost::beast::http::field::content_type, "application/json");
  req.set(boost::beast::http::field::content_length, body.length());
  req.body() = body;

  BOOST_LOG_TRIVIAL(trace) << body;

  // Send the HTTP request to the remote host

  boost::beast::http::async_write(_socket, req, yield[ec]);

  if (ec) {
    throw std::runtime_error("write : " + ec.message());
  }

  // Declare a container to hold the response
  Response res;

  boost::beast::http::async_read(_socket, _buffer, res, yield[ec]);

  if (ec) {
    throw std::runtime_error("read : " + ec.message());
  }

  return res;
}

// ----------------------------------------------------------------------------

Http::Response Http::put(const std::string &target, const nlohmann::json &body,
                         boost::asio::yield_context yield) {
  return write(boost::beast::http::verb::put, target, body.dump(), yield);
}

// ----------------------------------------------------------------------------

Http::Response Http::post(const std::string &target, const nlohmann::json &body,
                          boost::asio::yield_context yield) {
  return write(boost::beast::http::verb::post, target, body.dump(), yield);
}

// ----------------------------------------------------------------------------

Http::~Http() {
  boost::system::error_code ec;

  _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

  if (ec && ec != boost::system::errc::not_connected) {
    BOOST_LOG_TRIVIAL(trace) << "shutdown : " << ec.message();
  }
}

// ----------------------------------------------------------------------------

} // namespace client
} // namespace flex
