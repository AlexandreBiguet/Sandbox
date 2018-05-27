/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   21 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 26 - May - 2018
 */

#include <iostream>
#include <string>
#include <vector>

namespace Test1 {

class Vehicle {
 public:
  enum class Type { Undefined, Car, Boat };

  Type type() const { return _type; }

  virtual ~Vehicle() { std::cout << "Destroying a vehicle" << std::endl; }

 protected:
  Vehicle(Type type) : _type(type) {}

 private:
  Type _type;
};

class Car : public Vehicle {
 public:
  enum class Type { Ferrari, Audi };
  Type type() const { return _type; }

 protected:
  Car(Type type) : Vehicle(Vehicle::Type::Car), _type(type) {}

 private:
  Type _type;
};

class Ferrari : public Car {
 public:
  enum class Color { Red, Yellow };

  Ferrari(Color color) : Car(Car::Type::Ferrari), _color(color) {}

  Color color() const { return _color; }

  ~Ferrari() {
    std::string col((_color == Color::Red ? "Red" : "Yellow"));
    std::cout << "Destructing a " << col << " Ferrari \n";
  }

 private:
  Color _color;
};

class Audi : public Car {
 public:
  Audi(const std::string& name) : Car(Car::Type::Audi), _name(name) {}
  const std::string& name() const { return _name; }

  ~Audi() { std::cout << "destruct : " << _name << std::endl; }

 private:
  std::string _name;
};

class Boat : public Vehicle {
 public:
  enum class Type { Brig, Canoe };
  Type type() const { return _type; }

 protected:
  Boat(Type type) : Vehicle(Vehicle::Type::Boat), _type(type) {}

 private:
  Type _type;
};

class Brig : public Boat {
 public:
  Brig(size_t crewNumber) : Boat(Boat::Type::Brig), _crewNumber(crewNumber) {}
  size_t crewNumber() const { return _crewNumber; }

 private:
  size_t _crewNumber;
};

class VehicleHolder {
 public:
  template <typename Type>
  std::vector<std::shared_ptr<Vehicle> > get(Type type) const {
    std::vector<std::shared_ptr<Vehicle> > vec;
    for (const auto& elem : _vehicles) {
      if (elem->Vehicle::type() == type) {
        vec.push_back(elem);
      }
    }
    return vec;
  }

  VehicleHolder() = default;

  template <typename T>
  void add(std::shared_ptr<T> t) {
    _vehicles.push_back(t);
  }

 private:
  std::vector<std::shared_ptr<Vehicle> > _vehicles;
};

void test() {
  VehicleHolder holder;

  holder.add(std::make_shared<Brig>(12));
  holder.add(std::make_shared<Ferrari>(Ferrari::Color::Red));
  holder.add(std::make_shared<Audi>("a1"));
  holder.add(std::make_shared<Audi>("a4"));
  holder.add(std::make_shared<Ferrari>(Ferrari::Color::Yellow));
  holder.add(std::make_shared<Brig>(16));

  auto boats = holder.get(Vehicle::Type::Boat);

  for (const auto& boat : boats) {
    auto b = std::dynamic_pointer_cast<Boat>(boat);
    if (b->Boat::type() == Boat::Type::Brig) {
      auto brig = std::dynamic_pointer_cast<Brig>(b);
      std::cout << "Number of sailor : " << brig->crewNumber() << "\n";
    }
  }
}

}  // namespace Test1

int main() {
  Test1::test();
  std::cout << std::endl;
  return 0;
}
