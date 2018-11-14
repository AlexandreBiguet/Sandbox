/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   13 - Jun - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 14 - Nov - 2018
 */

/**
 * Testing boost::any stuff
 */

#include <iostream>
#include <vector>

#include <boost/any.hpp>

void test(const boost::any& value) {
  if (value.type() == typeid(int)) {
    std::cout << "Integer : " << boost::any_cast<int>(value) << std::endl;

  } else if (value.type() == typeid(float)) {
    std::cout << "Float : " << boost::any_cast<float>(value) << std::endl;

  } else if (value.type() == typeid(double)) {
    std::cout << "Double : " << boost::any_cast<double>(value) << std::endl;

  } else {
    try {
      std::cout << "String : " << boost::any_cast<std::string>(value)
                << std::endl;
    } catch (...) {
      try {
        std::cout << "\nchar * : " << boost::any_cast<char*>(value)
                  << std::endl;
      } catch (...) {
        // std::cout << "char[8] : " << boost::any_cast<std::array<char,
        // 8>>(value) << std::endl;
        std::cout << std::endl;
      }
    }
  }
}

int main() {
  std::vector<boost::any> values;

  values.emplace_back(120.0);
  values.emplace_back(120);
  values.emplace_back("bonjour");

  std::string str("toto");
  values.push_back(str);

  for (const auto& val : values) {
    std::cout << "----------\n";
    test(val);
  }

  return 0;
}
