//
//
//
#include <iostream>

#include <nlohmann/json.hpp>

int main() {
  auto json_msg = R"({ "mappings" : {
                     "_default_":{
                        "_timestamp" : {
                           "enabled" : true,
                           "store" : true
                      }}}})";

  try {
    nlohmann::json json = nlohmann::json::parse(json_msg);
    std::cout << json << std::endl;
  } catch(std::exception& exc) {
    std::cout << "cannot parse : " << exc.what() << std::endl;
    return -1;
  }
  return 0;
}