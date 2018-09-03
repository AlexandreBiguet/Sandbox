/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   01 - Sep - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 02 - Sep - 2018
 */

#include <iostream>

#include <boost/asio.hpp>

int main(int argc, char** argv) {
  const int default_sec(3);
  int sec(default_sec);

  if (argc > 1) {
    std::string arg(argv[1]);

    if (arg.find("-h") != std::string::npos ||
        arg.find("--help") != std::string::npos ||
        arg.find("help") != std::string::npos) {
      std::cout << "Performs a blocking wait for n seconds\n";
      std::cout << "Usage : boost_asio_timer1 [t=3] \n";
      return 0;
    }

    sec = std::atoi(argv[1]);

    if (sec < 0) {
      std::cout << "Cannot wait for a negative time\n";
      sec = default_sec;
    }
  }

  std::cout << "block wait during " << sec << " seconds \n";

  boost::asio::io_context io;

  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(sec));
  t.wait();

  std::cout << "waited : " << sec << " seconds" << std::endl;

  return 0;
}
