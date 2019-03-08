//
//
//

#include <chrono>
#include <cmath>
#include <iostream>

#include <boost/asio/signal_set.hpp>

#include <nlohmann/json.hpp>

#include <flex/producer/producer.hpp>

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

  flex::producer::Config cfg("/sine_producer");
  flex::producer::Producer producer(context, cfg);

  // SineProducer sine_prod;

  producer.run(SineProducer());

  boost::asio::signal_set signals(context, SIGINT, SIGTERM);

  signals.async_wait(
      [&context](const boost::system::error_code &, int) { context.stop(); });

  context.run();

  std::cout << "\n ------- \n All right \n";

  return EXIT_SUCCESS;
}