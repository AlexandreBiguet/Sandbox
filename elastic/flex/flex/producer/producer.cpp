#include "producer.hpp"

namespace flex {
namespace producer {

// ----------------------------------------------------------------------------

Producer::Producer(boost::asio::io_context &context, const Config &config)
    : _strand(context), _config(config), _timer(context), _client(context) {}

// ----------------------------------------------------------------------------

bool Producer::loop(boost::asio::yield_context yield) {
  _timer.expires_at(boost::asio::deadline_timer::traits_type::now() +
      boost::posix_time::milliseconds(_config._period_ms));

  boost::system::error_code ec;
  _timer.async_wait(yield[ec]);

  if (ec) {
    throw std::runtime_error("wait : " + ec.message());
  }
  return true;
}


} // namespace producer
} // namespace flex