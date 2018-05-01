//
//  main.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 29/04/2018 at 11:36.
//  Copyright © 2017 All rights reserved.
//  
//

/// 1) how to init an optional class member ?
/// 2) how to clear and re-init an optional class member

#include <iostream>
#include <utility>
#include <boost/optional.hpp>

///
/// \tparam T
template < typename T >
struct Object {

  /// Constructor
  /// \param data
  explicit Object(const T& data)
      : _data(data)
  { }

  /// Print
  void print() const {
    std::cout << _data << std::endl;
  }

  T _data;
};

///
/// \tparam T
template < typename T >
struct Object2 {

  /// Constructor
  /// \param one
  /// \param two
  explicit Object2(const T& one, const T& two )
      : _one(one), _two(two)
  { }

  /// Print
  void print() const {
    std::cout << _one << "  " << _two << std::endl;
  }

  T _one;
  T _two;
};


///
/// \tparam Obj
/// \tparam T
template <template<typename> class Obj, typename T>
struct ObjectHolder {

  /// Constructor
  /// \param data
  template <typename... Args>
  explicit ObjectHolder(Args&&... args)
      : _object(Obj<T>(std::forward<Args>(args)...))
  { }

  /// Getter
  /// \return
  const Obj<T> & object() const {
    return _object.get();
  }

  /// Clear
  void clear() {
    _object = boost::none;//boost::optional<Object<T>>();
  }

  /// Sets
  /// \param data
  template<typename... Args>
  void set(Args&&... args) {
    _object.emplace(std::forward<Args>(args)...);
  }

  /// Print
  void print() const {
    _object->print();
  }

  boost::optional< Obj<T> > _object;
};

int main () {

  {
    ObjectHolder<Object, double> holder(2.0);
    holder.print();

    holder.clear();
    holder.set(10.0);
    holder.print();
  }

  {
    ObjectHolder<Object2, int > holder(1, 2);
    holder.print();
    holder.clear();
    holder.set(10,20);
    holder.print();
    holder.set(15, 25);
    holder.print();
  }


  return 0;
}

// main.cpp ends here