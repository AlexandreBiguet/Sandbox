//
//  Variable.hpp 
//  snmpp
//
//  Created on 14/10/2017 at 18:55.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * This class represents a variable as used in a mathematical function.
 * A snmpp variable can be fixed or a parameter or a running-variable :
 * f(x,a,b) = ax + b
 * x, a and b are snmpp variables. You may want to solve f(x,a,b) = 0 for 'x'
 * at 'a' and 'b' fixed or you may want to solve f = 0 for 'b' at 'x' and 'a'
 * fixed.
 *
 * When a variable is of parameter type, it means that it is fixed when
 * solving e.g. f(x,p) = 0. But it is not fixed e.g. when finding p in a chi^2
 * minimization.
 *
 * A snmpp::variable is a snmpp::quantity for which a type has been added.
 ******************************************************************************/

/******************************************************************************
 * Class Attributes:
 * -----------------
 * _type : Type of the variable (defined in VariableType enum). Can be either
 *         Running, Fixed or Parameter
 *
 *  See protected attributes of snmpp::Quantity
 ******************************************************************************/

/******************************************************************************
 * Public Methods: 
 * ---------------
 * Constructor takes a VariableType as first argument and forward the other
 * arguments to the constructor of snmpp::Quantity
 ******************************************************************************/

/******************************************************************************
 * Private Methods:
 * ----------------
 * None
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include "Quantity.hpp"

namespace snmpp { namespace math {

enum class VariableType {Running, Fixed, Parameter};

template <typename ValueType>
class Variable : public snmpp::math::Quantity<ValueType> {

  private:

    VariableType _type;

  public:

    explicit Variable(VariableType type);
    Variable(double val, VariableType type);
    Variable(double val,double low, double high, VariableType type);

    VariableType getType() const;
    void setType(VariableType type);

    std::string typeToString()const;
    std::string toString() const override ;


};

/******************************************************************************
 * Implementation
 ******************************************************************************/

template<typename ValueType>
Variable<ValueType>::Variable(VariableType type) :_type(type) {}

template<typename ValueType>
Variable<ValueType>::Variable(double val, VariableType type)
    :Quantity<ValueType>(val), _type(type) {}

template<typename ValueType>
Variable<ValueType>::Variable
    (double val, double l, double h,VariableType type)
    :Quantity<ValueType>(val, l, h), _type(type) {}


template<typename ValueType>
VariableType Variable<ValueType>::getType() const {
    return _type;
}

template<typename ValueType>
void Variable<ValueType>::setType(VariableType type) {
    _type = type;
}

template<typename ValueType>
std::string Variable<ValueType>::typeToString() const {
    std::string s;
    switch (_type) {
        case VariableType::Running :
            s = "Running";
            break;
        case VariableType::Fixed:
            s = "Fixed";
            break;
        case VariableType::Parameter:
            s = "Parameter";
            break;
    }
    return s;
}

template<typename ValueType>
std::string Variable<ValueType>::toString() const {
    std::string s(Quantity<ValueType>::toString());
    s+=" type : " + typeToString();
    return s;
}

}} // namespace snmpp::math

// Variable.hpp ends here