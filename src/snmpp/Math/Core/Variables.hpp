//
//  Variables.hpp 
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
 * This class represents a map of variable
 ******************************************************************************/

/******************************************************************************
 * Class Attributes:
 * ----------------- 
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
 * 1) Check if it is more appropriate to use map or hash-map. My guess is that
 *    it depends on the number of variables...
 *
 * 2) It could be nice to construct a Variables from a vector of tuple and to
 *    forward the element of the tuples to the constructor of a Variable.
 ******************************************************************************/

#include <map>
#include <string>
#include <tuple>
//#include <type_traits>
//#include <utility>
#include <vector>

#include "Variable.hpp"

namespace snmpp { namespace math {

template <typename Key, typename ValueType>
class Variables{

  private:

    std::map<Key, Variable<ValueType> > _vars;

  public:

    using iterator = typename std::map<Key,Variable<ValueType>>::iterator;
    using const_iterator = typename std::map<Key, Variable<ValueType>>::const_iterator;

    explicit Variables(const std::map<Key, Variable<ValueType>> &vars);
    explicit Variables(const std::vector<std::tuple<Key,VariableType, ValueType>>&vars);

    iterator add(const Key &k, const Variable<ValueType> &v);

    std::map<Key,Variable<ValueType>> get() const;
    Variable<ValueType> get(const Key &k) const;


    /* std container interface stuff */

    iterator begin();
    iterator end();
    iterator find(const Key &k);

    const_iterator begin() const;
    const_iterator end()const;
    const_iterator find(const Key &k) const;

    bool empty() const;
    iterator erase(const_iterator it);
    std::size_t erase(const Key &t);
    void clear();
    std::size_t size();

  private :

};

/******************************************************************************
 * Implementation
 ******************************************************************************/

/**
 *
 * @tparam Key : key type
 * @tparam ValueType  : value type
 * @param vars : a std map of variables
 */

template <typename Key, typename ValueType>
Variables<Key,ValueType>::Variables
    (const std::map<Key, Variable<ValueType>> &vars) : _vars(vars){}

template <typename Key, typename ValueType>
Variables<Key,ValueType>::Variables(const std::vector<
    std::tuple<Key, VariableType, ValueType>> & vars) {

    for( const auto &i : vars ){

        auto p = _vars.emplace( std::get<0>(i),
                       Variable<ValueType>(std::get<1>(i), std::get<2>(i)));

        if ( !p.second ){
            throw std::logic_error("In construction of Variables : another "
                                       "element with same key already exists");
        }
    }
}

}} // namespace snmpp::math

// Variables.hpp ends here