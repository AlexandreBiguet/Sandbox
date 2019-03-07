#pragma once

#include <flex/client/http_client.hpp>

namespace flex {
namespace analyzer {

class Interface {
 public:
 private:
  client::HttpClient _client;
};

}  // namespace analyzer
}  // namespace flex
