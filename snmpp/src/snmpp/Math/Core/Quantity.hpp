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

namespace snmpp { namespace math { namespace core {

/**
 *
 * @tparam ValueType : type of the quantity hold in the Quantity object.
 *
 */
template < typename ValueType >
class Quantity {

  public:

    /**
     * Type of the interval for the quantity
     */
    using IntervalType = boost::numeric::interval<ValueType>;


    /***************************************************************************
     * Interface
     **************************************************************************/

  public:

    /**
     * Default constructor : The value is cast to 0 and interval is set to
     * ]-inf, +inf[
     *
     */
    Quantity();

    /**
     * Constructs a quantity with value @val and sets the interval of
     * definition to ]-inf, +inf[
     *
     **/
    explicit Quantity(const ValueType &val);

    /**
     * Constructs a quantity with value @val and interval to [@lower, @upper]
     *
     */
    Quantity(const ValueType &val, const ValueType &lower,
             const ValueType &upper);

    /**
     * Returns a copy of the value
     *
     */
    ValueType getValue() const;

    /**
     * Sets the value with @value
     *
     */
    void setValue(const ValueType &value);

    /**
     * Sets the lower bound of the interval to @lower
     *
     */
    void setLower(const ValueType &lower);

    /**
     * Sets the upper bound of the interval to @upper
     *
     */
    void setUpper(const ValueType &upper);

    /**
     * Sets the interval to [@lower, @upper]
     *
     */
    void setInterval(const ValueType &lower, const ValueType &upper);

    /**
     * Returns a copy of the lower bound of the interval
     *
     */
    ValueType getLower() const;

    /**
     * Returns a copy of the upper bound of the interval
     *
     */
    ValueType getUpper() const;

    /**
     * Returns a copy of the interval in a boost::numeric::interval object
     *
     */
    IntervalType getInterval() const;

    /**
     * Puts the quantity into a string
     * This is mainly for debug purpose
     *
     */
    virtual std::string toString()const;

    /***************************************************************************
     * Private
     **************************************************************************/

  protected:

    /**
     * The value hold by the Quantity object
     *
     */
    ValueType _value;

    /**
     * The interval of definition of the value
     *
     */
    IntervalType _interval;

};

/*******************************************************************************
 * Implementation
 ******************************************************************************/

/*******************************************************************************
 * Default constructor : The value is cast to 0 and interval is set to
 * ]-inf, +inf[
 *
 */

template< typename Type >
Quantity<Type>::Quantity() : _value(static_cast<Type>(0)) {
    _interval.set_whole();
}

/*******************************************************************************
 * Constructs a quantity with value @val and sets the interval of
 * definition to ]-inf, +inf[
 *
 **/

template< typename Type >
Quantity<Type>::Quantity(const Type &val) : _value(val) {
    _interval.set_whole();
}

/*******************************************************************************
 * Constructs a quantity with value @val and interval to [@lower, @upper]
 *
 */

template< typename Type >
Quantity<Type>::Quantity(const Type &val, const Type &lower, const Type &upper)
    : _value(val), _interval(lower, upper)
{}

/*******************************************************************************
 * Returns a copy of the value
 *
 */

template <typename Type>
Type Quantity<Type>::getValue() const {
    return _value;
}

/*******************************************************************************
 * Sets the value with @value
 *
 */

template <typename Type>
void Quantity<Type>::setValue(const Type &value) {
    _value = value;
}

/*******************************************************************************
 * Sets the lower bound of the interval to @lower
 *
 */

template <typename Type>
void Quantity<Type>::setLower(const Type &lower) {
    _interval.assign(lower, _interval.upper());
}

/*******************************************************************************
 * Sets the upper bound of the interval to @upper
 *
 */

template <typename Type>
void Quantity<Type>::setUpper(const Type &upper) {
    _interval.assign(_interval.lower(), upper);
}

/*******************************************************************************
 * Sets the interval to [@lower, @upper]
 *
 */

template <typename Type>
void Quantity<Type>::setInterval(const Type &lower, const Type &upper) {
    _interval.assign(lower, upper);
}

/*******************************************************************************
 * Returns a copy of the lower bound of the interval
 *
 */

template <typename Type>
Type Quantity<Type>::getLower() const {
    return _interval.lower();
}

/*******************************************************************************
 * Returns a copy of the upper bound of the interval
 *
 */

template <typename Type>
Type Quantity<Type>::getUpper() const {
    return _interval.upper();
}

/*******************************************************************************
 * Returns a copy of the interval in a boost::numeric::interval object
 *
 */

template <typename Type>
typename Quantity<Type>::IntervalType Quantity<Type>::getInterval() const {
    return _interval;
}

/*******************************************************************************
 * Puts the quantity into a string
 * This is mainly for debug purpose
 *
 */

template <typename Type>
std::string Quantity<Type>::toString()const{
    std::string s = std::to_string(_value) + " ["
        + std::to_string(_interval.lower()) + " ; "
        + std::to_string(_interval.upper()) + " ] ";
    return s;
}

}}} // namespace snmpp::math::core

// Quantity.hpp ends here