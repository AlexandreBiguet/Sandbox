//
//
//

#include <iostream>

#include <flex/client/http.hpp>

int main() {

  // The io_context is required for all I/O
  boost::asio::io_context context;

  std::string target{"/twitter/_doc/0"};

  flex::client::Http client(context);

  nlohmann::json json;
  json["user"] = "kimchy";
  json["post_date"] = "2009-11-15T14:12:12";
  json["message"] = "Hello, elastic search";

  boost::asio::spawn(
      context, [&client, &target, &json](boost::asio::yield_context yield) {
        client.connect(yield);

        boost::system::error_code ec;

        auto res = client.put(target, json, yield[ec]);

        if (ec) {
          throw std::runtime_error("put : " + ec.message());
        }
        std::cout << res.body() << std::endl;
      });

  context.run();

  std::cout << "\n ------- \n All right \n";

  return EXIT_SUCCESS;
}
