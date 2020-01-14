#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

namespace {

class Shape {
 public:
  using ptr = std::unique_ptr<Shape>;

  virtual unsigned int GetArea() const = 0;
  virtual ~Shape() = default;
};

class Rectangle : public Shape {
 public:
  using ptr = std::unique_ptr<Rectangle>;

  Rectangle(unsigned int height, unsigned int width) : _height(height), _width(width) {}

  unsigned int GetArea() const override { return _height * _width; }

  ~Rectangle() override = default;

  static ptr Create(unsigned int height, unsigned int width) { return std::make_unique<Rectangle>(height, width); }

 private:
  unsigned int _height;
  unsigned int _width;
};

class Triangle : public Shape {
 public:
  using ptr = std::unique_ptr<Triangle>;

  Triangle(unsigned int height, unsigned int width) : _height(height), _width(width) {}

  unsigned int GetArea() const override {
    double area = 0.5 * _height * _width;
    return std::round(area);
  }

  ~Triangle() override = default;

  static ptr Create(unsigned int height, unsigned int width) { return std::make_unique<Triangle>(height, width); }

 private:
  unsigned int _height;
  unsigned int _width;
};

class Circle : public Shape {
 public:
  using ptr = std::unique_ptr<Circle>;

  explicit Circle(unsigned int radius) : _radius(radius) {}

  unsigned int GetArea() const override {
    double area = M_PI * _radius * _radius;
    return std::round(area);
  }

  ~Circle() override = default;

  static ptr Create(int radius) { return std::make_unique<Circle>(radius); }

 private:
  unsigned int _radius;
};

}  // namespace

int main() {

  std::vector<Shape::ptr> shapes;
  shapes.push_back(Rectangle::Create(4, 3));
  shapes.push_back(Triangle::Create(5, 2));
  shapes.push_back(Circle::Create(5));

  for (const auto& shape : shapes) {
    std::cout << shape->GetArea() << std::endl;
  }

  return EXIT_SUCCESS;
}