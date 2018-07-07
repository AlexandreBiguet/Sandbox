#include "chat_handler.hpp"
#include "generic_server.hpp"

int main() {
  Sandbox::asio_generic_server<Sandbox::chat_handler> server;
  server.start_server(8888);
  return 0;
}
