//
//
//

#pragma once

#include <string>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>

#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

#include <nlohmann/json.hpp>

namespace flex {
namespace io {
namespace client {

class Http {
public:
  using Request = boost::beast::http::request<boost::beast::http::string_body>;

  using Response =
      boost::beast::http::response<boost::beast::http::string_body>;

  struct Config {

    Config(std::string &&host, std::string &&port);
    static Config createDefault();

    std::string _host;
    std::string _port;
  };

  explicit Http(boost::asio::io_context &context,
                const Config &config = Config::createDefault());

  void connect(boost::asio::yield_context yield);

  Response get(const std::string &target, boost::asio::yield_context yield);

  Response put(const std::string &target, const nlohmann::json &body,
               boost::asio::yield_context yield);

  Response post(const std::string &target, const nlohmann::json &body,
                boost::asio::yield_context yield);

  ~Http();

private:
  Response write(boost::beast::http::verb verb, const std::string &target,
                 const std::string &body, boost::asio::yield_context yield);

  Config _config;

  boost::asio::ip::tcp::resolver _resolver;
  boost::asio::ip::tcp::socket _socket;
  boost::beast::flat_buffer _buffer;

  const int _http_version{11};
};

} // namespace client
} // namespace io
} // namespace flex
