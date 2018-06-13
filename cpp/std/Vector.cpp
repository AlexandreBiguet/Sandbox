/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   13 - Jun - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

#include <iostream>
#include <vector>

void print(const std::vector<int>& v) {
  for (const auto& it : v) {
    std::cout << it << std::endl;
  }
}

void reserveAndClear() {
  /**
   * 1- Does the clear method changes the capacity of a vector ?
   * 2- What is the effect of the reserve method when reserving a number less
   * than the capacity ?
   * */

  std::vector<int> v1;
  const int N = 50;
  v1.reserve(N);
  v1.push_back(10);
  std::cout << "reserve [" << N << "] \n";

  std::cout << "Adding 5 elements to the vector \n";

  for (int i = 0; i < 5; ++i) {
    v1.push_back(i);
  }

  std::cout << "v1 size     : " << v1.size() << std::endl;
  std::cout << "v1 capacity : " << v1.capacity() << std::endl;

  print(v1);

  std::cout << "\nreserve [0] \n";

  v1.reserve(0);

  std::cout << "v1 size     : " << v1.size() << std::endl;
  std::cout << "v1 capacity : " << v1.capacity() << std::endl;
  v1.push_back(1345);
  print(v1);

  std::cout << "\nclear \n";
  v1.clear();

  std::cout << "v1 size     : " << v1.size() << std::endl;
  std::cout << "v1 capacity : " << v1.capacity() << std::endl;
  print(v1);

  /**
   * 1- The clear method does not modify the capacity of a vector
   * 2- No effect on the size nor the capacity (pushing back add an element to
   * the end of the vector as expected)
   * */
}

void resizeAndReserve() {
  /**
   * Difference between resize and reserve (std::vector)
   */

  std::vector<int> v1, v2;
  const std::size_t size(20);
  v1.reserve(size);
  v2.resize(size);

  v1.push_back(100);
  v2.push_back(100);

  std::cout << "v1 [reserve] size : " << v1.size() << std::endl;
  std::cout << "v2 [resize ] size : " << v2.size() << std::endl;

  printf("%15s %15s \n", "Reserve", "Resize");

  for (size_t i = 0; i < v1.size(); ++i) {
    try {
      printf("%15d %15d \n", v1[i], v2[i]);
    } catch (const std::out_of_range& e) {
      std::cout << "out of range error when accessing [i:" << i << "] \n";
    } catch (const std::exception& e) {
      std::cout << " -> error : " << e.what() << std::endl;
    }
  }

  /**
   * reserve affects the capacity of the vector
   * resize affects its size
   * Since a push_back pushes an element at the end of the vector the expected
   * output is : Reserve        Resize 100            0
   * */
}

int main() {
  reserveAndClear();
  resizeAndReserve();
  return 0;
}
