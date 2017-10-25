//
//  FuncBase.hpp 
//  snmpp
//
//  Created on 14/10/2017 at 18:56.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * Virtual class
 * Represents a function
 ******************************************************************************/

/******************************************************************************
 * Class Attributes:
 * -----------------
 * _inputs  : a Variables<K,V> object. Input Variables
 * _outputs : Output Variables in a map<Key, Value> object
 ******************************************************************************/

/******************************************************************************
 * Public Methods: 
 * ---------------
 ******************************************************************************/

/******************************************************************************
 * Private Methods:
 * ----------------
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include "Variables.hpp"

namespace snmpp { namespace math { namespace core {

template<typename Key, typename ValueType>
class FuncBase {

  public:

    using ConstructorInputType = Variables<Key, ValueType>;
    using InputType  = std::map<Key, ValueType>;
    using OutputType = std::map<Key, ValueType>;

  protected:

    ConstructorInputType _inputs;
    OutputType _outputs;

  public:

    explicit FuncBase(const ConstructorInputType &vars) : _inputs(vars) {}

    const OutputType &operator()() {
        eval();
        return _outputs;
    }

    const OutputType &operator()(const InputType &vars) {
        _inputs.setFromMap(vars);
        eval();
        return _outputs;
    }

    OutputType getCopy() const {
        return _outputs;
    }

    virtual void eval() = 0;
};

} // namespace core

using FuncBase = core::FuncBase<std::string,double>;

}} // namespace snmpp::math

// FuncBase.hpp ends here