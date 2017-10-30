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

#include "Variables.hpp"

namespace snmpp { namespace math { namespace core {

template<typename Key, typename ValueType>
class FuncBase {


    /***************************************************************************
     * Interface
     **************************************************************************/

  public:

    using ConstructorInputType = Variables<Key, ValueType>;
    using InputType  = std::map<Key, ValueType>;
    using OutputType = std::map<Key, ValueType>;

    /**
     * Constructor from a core::Variables
     *
     * */

    explicit FuncBase(const ConstructorInputType &vars) : _inputs(vars) {}

    /**
     * operator() overloading with no argument
     *
     * */

    const OutputType &operator()() {
        eval();
        return _outputs;
    }

    /**
     * Operator() overloading with a map<Key, ValueType> argument
     *
     * */

    const OutputType &operator()(const InputType &vars) {
        _inputs.setFromMap(vars);
        eval();
        return _outputs;
    }

    /**
     * Returns a copy of the calculated outputs
     *
     * */

    OutputType getCopy() const {
        return _outputs;
    }

    /**
     * Returns a const reference to its variables
     *
     * */

    const ConstructorInputType & getVariables()const {
        return _inputs;
    }

    /**
     * Returns true if @var is contained in the function variables, false
     * otherwise.
     * */
    bool hasVariable(const Key &var ){
        auto it = _inputs.find(var);
        if ( it == _inputs.end() ){
            return false;
        }
        return true;
    }


    /**
     * Pure virtual eval method
     *
     * */

    virtual void eval() = 0;

    /***************************************************************************
     * Protected Attributes
     **************************************************************************/

  protected:

    ConstructorInputType _inputs;
    OutputType _outputs;

};

} // namespace core

using FuncBase = core::FuncBase<std::string,double>;

}} // namespace snmpp::math

// FuncBase.hpp ends here