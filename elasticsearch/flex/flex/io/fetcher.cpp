//
//
//

#include "fetcher.hpp"

#include <future>

#include <boost/asio/spawn.hpp>
#include <boost/log/trivial.hpp>

namespace flex {
namespace io {

// ----------------------------------------------------------------------------

Fetcher::Fetcher(boost::asio::io_context &context,
                 const Fetcher::Config &config)
    : _strand(context), _timer(context), _client(context), _config(config),
      _buffer(config._cacheSize) {}

// ----------------------------------------------------------------------------

void Fetcher::run() {

  boost::asio::spawn( // ....
      _strand.get_io_context(), [this](boost::asio::yield_context yield) {

        _client.connect(yield);

        while (loop(yield)) {
          auto res = _client.get(_config._index + "/_doc/1", yield);
          try {
            _buffer.push_back(nlohmann::json::parse(res.body()));
            BOOST_LOG_TRIVIAL(trace) << _buffer[0];
          } catch (...) {
            BOOST_LOG_TRIVIAL(warning)
                << "could not parse response body " << res.body();
          }
        }
      });
}

// ----------------------------------------------------------------------------

void Fetcher::get(const onGetData& handler) {

  boost::asio::post(_strand, [this, handler]() {
    handler(std::vector<DataType>(_buffer.begin(), _buffer.end()), nullptr);
    return;
  });

}

// ----------------------------------------------------------------------------

std::vector<Fetcher::DataType> Fetcher::get() {

  std::promise<std::vector<DataType>> promise;
  auto future = promise.get_future();

  _strand.get_io_context().poll();

  boost::asio::spawn( // ...
      _strand.get_io_context(), [this, &promise](boost::asio::yield_context yield) {
        std::vector<DataType> data (std::begin(_buffer), std::end(_buffer));
        promise.set_value(data);
      });

  try {
    return future.get();
  } catch (...) {
    BOOST_LOG_TRIVIAL(error) << "could not retrieve data \n";
  }
  return {};

}

// ----------------------------------------------------------------------------

bool Fetcher::loop(boost::asio::yield_context yield) {
  _timer.expires_at(
      boost::asio::deadline_timer::traits_type::now() +
      boost::posix_time::milliseconds(_config._retrievePeriod_ms));

  boost::system::error_code ec;
  _timer.async_wait(yield[ec]);

  if (ec) {
    throw std::runtime_error("wait : " + ec.message());
  }
  return true;
}

// ----------------------------------------------------------------------------

} // namespace io
} // namespace flex
