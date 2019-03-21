//
//
//

#include <iostream>

#include <boost/circular_buffer.hpp>

int main() {
  const std::size_t size{10};

  boost::circular_buffer<int> cb(size);

  for (size_t i = 0; i < size; ++i) {
    cb.push_back(i);
  }

  std::cout << "Expected: \n0, 1, 2, 3, 4, 5, 6, 7, 8, 9\n";

  std::for_each(std::begin(cb), std::end(cb),
                [](const auto &e) { std::cout << e << ", "; });
  std::cout << "\n\n";

  cb.push_back(10);
  cb.push_back(11);

  std::cout << "Expected: \n2, 3, 4, 5, 6, 7, 8, 9, 10, 11\n";

  std::for_each(std::begin(cb), std::end(cb),
                [](const auto &e) { std::cout << e << ", "; });
  std::cout << std::endl;

  return 0;
}
