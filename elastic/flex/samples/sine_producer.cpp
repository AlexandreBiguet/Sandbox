//
//
//

#include <chrono>
#include <cmath>
#include <iostream>

#include <boost/asio/signal_set.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>

#include <nlohmann/json.hpp>

#include <flex/io/producer.hpp>

class SineProducer {
public:
  SineProducer() : _start(std::chrono::system_clock::now()) {}

  nlohmann::json operator()() const {
    std::chrono::duration<double> t = std::chrono::system_clock::now() - _start;
    nlohmann::json _json;
    _json["name"] = "sine_producer";
    auto val = t.count();
    _json["value"] = val;
    _json["sine"] = std::sin(val);
    return _json;
  }

private:
  std::chrono::system_clock::time_point _start;
};

int main() {

  boost::asio::io_context context;

  flex::io::Producer::Config cfg("sine_producer");

  flex::io::Producer producer(context, cfg);

  boost::log::core::get()->set_filter(boost::log::trivial::severity >=
                                      boost::log::trivial::trace);

  producer.run(SineProducer());

  boost::asio::signal_set signals(context, SIGINT, SIGTERM);

  signals.async_wait(
      [&context](const boost::system::error_code &, int) { context.stop(); });

  context.run();

  std::cout << "\n ------- \n All right \n";

  return EXIT_SUCCESS;
}
