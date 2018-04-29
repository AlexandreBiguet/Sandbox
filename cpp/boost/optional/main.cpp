//
//  main.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 29/04/2018 at 11:36.
//  Copyright © 2017 All rights reserved.
//  
//

/// how to init an optionnal class member ?

#include <iostream>

#include <boost/optional.hpp>

template < typename T >
struct Object {
  explicit Object(const T& data) : _data(data) { }
  T _data;
};

template <typename T>
struct ObjectHolder {
  explicit ObjectHolder(const T& data) : _object(data) { }

  const Object<T>& object() const {
    return _object.get();
  }

  boost::optional<Object<T>> _object;
};

int main () {

  ObjectHolder<double> holder(2.0);
  std::cout << holder.object()._data << std::endl;

  return 0;
}

// main.cpp ends here