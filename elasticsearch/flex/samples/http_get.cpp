//
//
//

#include <iostream>

#include <flex/io/client/http.hpp>

int main() {

  // The io_context is required for all I/O
  boost::asio::io_context context;

  std::string target{"/twitter/_doc/0"};

  flex::io::client::Http client(context);

  boost::asio::spawn(
      context, [&client, &target](boost::asio::yield_context yield) {
        client.connect(yield);

        boost::system::error_code ec;

        auto res = client.get(target, yield[ec]);

        if (ec) {
          throw std::runtime_error("get : " + ec.message());
        }
        std::cout << res.body() << std::endl;
      });

  context.run();

  std::cout << "\n ------- \n All right \n";

  return EXIT_SUCCESS;
}
