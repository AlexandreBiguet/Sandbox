//
//
//
#include <iostream>
#include <thread>

#include <boost/asio/signal_set.hpp>

#include <flex/io/fetcher.hpp>

int main() {
  boost::asio::io_context context;

  flex::io::Fetcher::Config cfg("sine_producer");

  flex::io::Fetcher fetcher(context, cfg);

  boost::asio::signal_set signals(context, SIGINT, SIGTERM);

  signals.async_wait(
      [&context](const boost::system::error_code &, int) { context.stop(); });

  fetcher.run();

  boost::asio::steady_timer timer(context);
  timer.expires_after(std::chrono::duration<long long, std::ratio<1>>(5));
  timer.async_wait([&fetcher](boost::system::error_code) {
    fetcher.get([](const std::vector<flex::io::Fetcher::DataType> &vec,
                   std::exception_ptr error) {
      if (!error) {
        std::cout << "number of element : " << vec.size() << std::endl;
        std::for_each(std::begin(vec), std::end(vec),
                      [](const auto &e) { std::cout << e.dump(2) << "\n\n"; });
      } else {
        std::cout << "could not get buffer \n";
      }
    });
  });

  boost::asio::steady_timer timer2(context);
  timer2.expires_after(std::chrono::duration<long long, std::ratio<1>>(7));
  timer2.async_wait([&fetcher](boost::system::error_code) {
    auto vec = fetcher.get();
    std::cout << "number of element : " << vec.size() << std::endl;
    std::for_each(std::begin(vec), std::end(vec),
                  [](const auto &e) { std::cout << e.dump(2) << "\n\n"; });
  });

  //   auto data = fetcher.get();

  //  context.post([&fetcher]() {
  //    auto data = fetcher.get();
  //    std::for_each(std::begin(data), std::end(data), [](const auto &e) {
  //      std::cout << e.dump(2) << "\n\n";
  //    });
  //  });

  context.run();

  std::cout << "\n ------- \n All right \n";

  return EXIT_SUCCESS;
}
