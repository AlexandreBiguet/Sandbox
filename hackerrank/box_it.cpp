#include <iostream>
#include <sstream>
#include <string>

#define READ_FROM_STDIN

// Implement the class Box
// l,b,h are integers representing the dimensions of the box

// The class should have the following functions :

// Constructors:
// Box();
// Box(int,int,int);
// Box(Box);

// int getLength(); // Return box's length
// int getBreadth (); // Return box's breadth
// int getHeight ();  //Return box's height
// long long CalculateVolume(); // Return the volume of the box

// Overload operator < as specified
// bool operator<(Box& b)

// Overload operator << as specified
// ostream& operator<<(ostream& out, Box& B)

class Box {
 public:
  Box() = default;
  Box(int length, int breadth, int height) : _length{length}, _breadth{breadth}, _height{height} {}
  Box(const Box& rhs) = default;

  int getLength() { return _length; }
  int getBreadth() { return _breadth; }
  int getHeight() { return _height; }
  long long CalculateVolume() { return getLength() * getBreadth() * getHeight(); }

  bool operator<(const Box& other) {
    auto comp_1 = [](const Box& lhs, const Box& rhs) { return lhs._length < rhs._length; };

    auto comp_2 = [](const Box& lhs, const Box& rhs) {
      return lhs._breadth < rhs._breadth && lhs._length == rhs._length;
    };

    auto comp_3 = [](const Box& lhs, const Box& rhs) {
      return lhs._height < rhs._height && lhs._breadth == rhs._breadth && lhs._length == rhs._length;
    };

    if (this->_height == other._height && this->_breadth == other._breadth && this->_length == other._length) {
      return false;
    }

    return comp_1(*this, other) || comp_2(*this, other) || comp_3(*this, other);
  }

  std::string to_string() const {
    std::stringstream stream;
    stream << _length << " " << _breadth << " " << _height;
    return stream.str();
  }

  friend std::ostream& operator<<(std::ostream& stream, const Box& box) {
    stream << box.to_string();
    return stream;
  }

 private:
  int _length{0};
  int _breadth{0};
  int _height{0};
};

void check2() {
  int n;
  std::cin >> n;
  Box temp;
  for (int i = 0; i < n; i++) {
    int type;
    std::cin >> type;
    if (type == 1) {
      std::cout << temp << std::endl;
    }
    if (type == 2) {
      int l, b, h;
      std::cin >> l >> b >> h;
      Box NewBox(l, b, h);
      temp = NewBox;
      std::cout << temp << std::endl;
    }
    if (type == 3) {
      int l, b, h;
      std::cin >> l >> b >> h;
      Box NewBox(l, b, h);
      if (NewBox < temp) {
        std::cout << "Lesser\n";
      } else {
        std::cout << "Greater\n";
      }
    }
    if (type == 4) {
      std::cout << temp.CalculateVolume() << std::endl;
    }
    if (type == 5) {
      Box NewBox(temp);
      std::cout << NewBox << std::endl;
    }
  }
}

int main() {
#ifdef READ_FROM_STDIN
  check2();
#else

  Box box_1(10, 5, 3);

  std::cout << "default box: " << box_1 << std::endl;

  {
    Box box_2(11, 5, 3);

    if (not(box_1 < box_2)) {
      std::cout << "comparison comp1 failed" << std::endl;
      return EXIT_FAILURE;
    }

    std::cout << " comp1 : ok \n";
  }

  {
    Box box_2(10, 6, 3);
    if (not(box_1 < box_2)) {
      std::cout << "comparison comp2 failed" << std::endl;
      return EXIT_FAILURE;
    }
    std::cout << " comp2 : ok \n";
  }

  {
    Box box_2(10, 5, 4);
    if (not(box_1 < box_2)) {
      std::cout << "comparison comp3 failed" << std::endl;
      return EXIT_FAILURE;
    }
    std::cout << " comp3 : ok \n";
  }

  {
    Box box_2(10, 5, 4);
    std::cout << "box: " << box_2 << " ---- volume : " << box_2.CalculateVolume() << " (10 * 5 * 4 = 200)" << std::endl;
  }

  {
    Box box_2(10, 5, 4);
    Box box_cpy(box_2);

    std::cout << " initial box " << box_2 << "\n"
              << " copy const box " << box_cpy << "\n";

    Box box_eq = box_2;
    std::cout << " = operator " << box_eq << std::endl;
  }

#endif

  return EXIT_SUCCESS;
}