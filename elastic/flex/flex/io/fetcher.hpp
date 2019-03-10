//
//
//

#pragma once

#include <cstddef>
#include <memory>
#include <string>

#include <boost/asio/io_context.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/optional.hpp>
#include <boost/circular_buffer.hpp>

#include <flex/io/client/http.hpp>

namespace flex {
namespace io {

/// \brief Pull data from Elastic Search and
class Fetcher {
public:
  using DataType = nlohmann::json;

  using onGetData = std::function<void(const std::vector<Fetcher::DataType>& data, const std::exception_ptr)>;

  struct Config {
    explicit Config(std::string &&index) : _index(std::move(index)) {}

    std::string _index;
    std::size_t _retrievePeriod_ms{1500};
    std::size_t _cacheSize{200};
  };

  Fetcher(boost::asio::io_context& context, const Config& config);

  void run();

  /// \brief Access data Callback version
  /// \param handler
  void get(const onGetData& handler);

  /// \brief Access data
  /// \note blocks until data is ready
  /// \return
  std::vector<DataType> get();

private:
  bool loop(boost::asio::yield_context yield);

  boost::optional<std::size_t> _lastId;
  boost::circular_buffer<DataType> _buffer;

  boost::asio::io_context::strand _strand;
  boost::asio::deadline_timer _timer;
  client::Http _client;
  Config _config;
};

} // namespace io
} // namespace flex
