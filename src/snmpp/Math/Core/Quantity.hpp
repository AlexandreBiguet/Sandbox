//
//  Quantity.hpp 
//  snmpp
//
//  Created on 14/10/2017 at 18:54.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * This class represents a general quantity which is determined by its value
 * and its interval of definition.
 ******************************************************************************/

/******************************************************************************
 * Class Attributes:
 * -----------------
 * _value : the actual value of the corresponding quantity
 * _interval : the interval of definition of this quantity
 ******************************************************************************/

/******************************************************************************
 * Public Methods: 
 * ---------------
 * Constructors:
 *    Quantity() :
 *      value initialized to 0 and interval initialized to ]-inf;+inf[
 *
 *    Quantity(const Type &val) :
 *      value initialized to val and interval init. to whole
 *
 *     Quantity(const Type &val, const Type &lower, const Type &upper) :
 *      value init to val and interval init to [lower, upper]
 *
 * Getters and Setters -> see interface
 *
 * std::string toString() : debug only
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
#include <string>

#include <boost/numeric/interval.hpp>

namespace snmpp { namespace math {

template < typename ValueType >
class Quantity {

  public:

    using IntervalType = boost::numeric::interval<ValueType>;

  protected:
    ValueType _value;
    IntervalType _interval;

  public:
    Quantity();
    explicit Quantity(const ValueType &val);
    Quantity(const ValueType &val, const ValueType &lower, const ValueType &upper);

    ValueType getValue() const;
    void setValue(const ValueType &v);
    void setLower(const ValueType &v);
    void setUpper(const ValueType &v);
    void setInterval(const ValueType &lower, const ValueType &upper);
    ValueType getLower() const;
    ValueType getUpper() const;
    IntervalType getInterval() const;
    virtual std::string toString()const;
};

/******************************************************************************
 * Implementation
 ******************************************************************************/

template< typename Type >
Quantity<Type>::Quantity() : _value(static_cast<Type>(0)) {
    _interval.set_whole();
}

template< typename Type >
Quantity<Type>::Quantity(const Type &val) : _value(val) {
    _interval.set_whole();
}

template< typename Type >
Quantity<Type>::Quantity(const Type &val, const Type &lower, const Type &upper)
    : _value(val), _interval(lower, upper)
{}

template <typename Type>
Type Quantity<Type>::getValue() const {
    return _value;
}

template <typename Type>
void Quantity<Type>::setValue(const Type &v) {
    _value = v;
}

template <typename Type>
void Quantity<Type>::setLower(const Type &v) {
    _interval.assign(v, _interval.upper() );
}

template <typename Type>
void Quantity<Type>::setUpper(const Type &v) {
    _interval.assign(_interval.lower(), v);
}

template <typename Type>
void Quantity<Type>::setInterval(const Type &lower, const Type &upper) {
    _interval.assign(lower, upper);
}

template <typename Type>
Type Quantity<Type>::getLower() const {
    return _interval.lower();
}

template <typename Type>
Type Quantity<Type>::getUpper() const {
    return _interval.upper();
}

template <typename Type>
typename Quantity<Type>::IntervalType Quantity<Type>::getInterval() const {
    return _interval;
}

template <typename Type>
std::string Quantity<Type>::toString()const{
    std::string s = std::to_string(_value) + " ["
        + std::to_string(_interval.lower()) + " ; "
        + std::to_string(_interval.upper()) + " ] ";
    return s;
}

}} // namespace snmpp::math

// Quantity.hpp ends here