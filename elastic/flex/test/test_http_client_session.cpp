//
//  Created by Alexandre Biguet on 2019-03-07 at 16:05.
//

#include <iostream>
#include <memory>

// HttpClient

#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/dynamic_body.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/version.hpp>

// main
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/signal_set.hpp>

#include <boost/log/trivial.hpp>

namespace {

/// \brief
class HttpClient {

public:
  /// \brief
  struct Config {

    Config(std::string &&host, std::string &&port)
        : _host(std::move(host)), _port(std::move(port)) {}

    static Config createDefault() { return Config("localhost", "9200"); }

    std::string _host;
    std::string _port;
  };

  /// \brief
  /// \param context
  /// \param config
  explicit HttpClient(boost::asio::io_context &context,
                      const Config &config = Config::createDefault())
      : _config(config), _resolver(context), _socket(context) {}

  /// \brief
  void connect(boost::asio::yield_context yield) {

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

  /// \brief
  /// \param target
  boost::beast::http::response<boost::beast::http::string_body>
  get(const std::string &target, boost::asio::yield_context yield) {

    boost::system::error_code ec;

    boost::beast::http::request<boost::beast::http::string_body> req{
        boost::beast::http::verb::get, target, _http_version};
    req.set(boost::beast::http::field::host, _config._host);
    req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Send the HTTP request to the remote host
    boost::beast::http::async_write(_socket, req, yield[ec]);

    if (ec) {
      throw std::runtime_error("write : " + ec.message());
    }

    // Declare a container to hold the response
    boost::beast::http::response<boost::beast::http::string_body> res;

    boost::beast::http::async_read(_socket, _buffer, res, yield[ec]);

    if (ec) {
      throw std::runtime_error("read : " + ec.message());
    }

    return res;
  }

  ~HttpClient() {

    boost::system::error_code ec;

    _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

    if (ec && ec != boost::system::errc::not_connected) {
      std::cerr << "shutdown : " << ec.message() << std::endl;
    }
  }

private:
  Config _config;

  boost::asio::ip::tcp::resolver _resolver;
  boost::asio::ip::tcp::socket _socket;
  boost::beast::flat_buffer _buffer;

  const int _http_version{11};
};

template <typename BodyType>
void print_response(const boost::beast::http::response<BodyType> &res) {

  BOOST_LOG_TRIVIAL(trace) << res.body() << "\n";
}

void wait(boost::asio::io_context &context, boost::asio::yield_context yield,
          size_t timeout_ms = 500) {
  boost::asio::deadline_timer timer(context);
  timer.expires_at(boost::asio::deadline_timer::traits_type::now() +
                   boost::posix_time::milliseconds(timeout_ms));
  boost::system::error_code ec;
  timer.async_wait(yield[ec]);

  if (ec) {
    throw std::runtime_error("wait : " + ec.message());
  }
}

} // namespace

int main(int argc, char **argv) {

  std::string target{"/twitter"};

  if (argc == 2) {
    target = argv[1];
  }

  // The io_context is required for all I/O
  boost::asio::io_context context;

  HttpClient client(context);

  boost::asio::spawn(
      context, [&context, &client, &target](boost::asio::yield_context yield) {
        client.connect(yield);

        while (true) {
          print_response(client.get(target, yield));
          wait(context, yield, 1000);
        }
      });

  boost::asio::signal_set signals(context, SIGINT, SIGTERM);

  signals.async_wait(
      [&context](const boost::system::error_code &, int) { context.stop(); });

  context.run();

  std::cout << "\n ------- \n All right \n";

  return EXIT_SUCCESS;
}