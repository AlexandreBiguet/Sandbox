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
 * It has the std::container interface.
 ******************************************************************************/

/******************************************************************************
 * Class Attributes:
 * -----------------
 * _vars : this is the map of variable
 ******************************************************************************/

/******************************************************************************
 * Public Methods: 
 * ---------------
 * A lot : see interface
 ******************************************************************************/

/******************************************************************************
 * Private Methods:
 * ----------------
 * Nono for now
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 * 1) Check if it is more appropriate to use map or hash-map. My guess is that
 *    it depends on the number of variables...
 *
 ******************************************************************************/

#include <map>
#include <vector>


#include "Variable.hpp"

namespace snmpp { namespace math {

/**
 * The Variables class is a container of Variables acting like a map with
 * key @Key and value @ValueType
 *
 * It implements iterators and can be used as a std::container
 *
 * */
template <typename Key, typename ValueType>
class Variables{

  private :

    /**
     * Private typedef used as an argument in a constructor.
     *
     * */
    using OtherVarContainer = std::vector<std::tuple<Key,ValueType,VariableType>>;


    /***************************************************************************
     * Interface
     **************************************************************************/
  public:

    /**
     * The low lying std::container used
     *
     * */
    using VariablesContainer = std::map<Key, Variable<ValueType>>;

    /**
     * Definition of iteretors as the VariablesContainer iterators
     *
     * */
    using iterator = typename VariablesContainer::iterator;
    using const_iterator = typename VariablesContainer::const_iterator;
    using reverse_iterator = typename VariablesContainer::reverse_iterator;
    using const_reverse_iterator =
        typename VariablesContainer::const_reverse_iterator;

    /**
     * Default construction
     *
     * */
    Variables();

    /**
     * Construction from a VariablesContainer
     *
     * */
    explicit Variables(const VariablesContainer &vars);

    /**
     * Construction from a vector of tuple. The tuple contains the key and
     * (value and VariableType).
     * OtherVarContainer is private.
     *
     * */
    explicit Variables(const OtherVarContainer &vars);

    /**
     * Add a variable @v inside the container with key @k.
     * Returns an iterator to this newly inserted variable.
     *
     * Throws if it was not possible to add this variable with the given key.
     *
     * */
    iterator add(const Key &k, const Variable<ValueType> &v);

    /**
     * Returns a copy of the low lying container
     *
     * */
    VariablesContainer get() const;

    /**
     * Returns a copy of the Variable contained in the VariablesContainer at
     * key @k.
     *
     * Throws if no element with key @k was found.
     *
     * */
    Variable<ValueType> get(const Key &k) const;

    /**
     * Returns a vector of const_iterator pointing to the variables of
     * VariableType @type in the container.
     *
     * Returns an empty vector if no variable of type @type was found.
     * */
    std::vector< const_iterator > get( VariableType type) const;

    /**
     * Returns a vector of Key (copied) of the variable of VariableType @type
     *
     * */
    std::vector<Key> getKeys (VariableType type)const;

    /**
     * Sets the value @v of a Variable with key @k
     *
     * Throws if the key @k was not found in the container
     *
     * */
    void set(const Key &k, const ValueType &v);

    /**
     * Call the previous set method for each element of the input vector
     *
     * Throws if a key was not found in the low-lying container
     *
     * */
    void set(const std::vector<std::pair<Key, ValueType>> &val);

    /**
     * Equivalent to previous set method but for rvalue reference
     *
     * */
    void set(std::vector<std::pair<Key, ValueType>> &&val);

    /**
     * Sets the current Variables object with another Variables object
     *
     * Throw if a key of the input object is not already defined in the
     * current Variables object
     *
     * */
    void setFromVariables(Variables<Key, ValueType> vars);

    /**
     * Sets the current Variables object with a map of Key, value
     *
     * Throw if a key of the input object is not already defined in the
     * current Variables object
     *
     * */
    void setFromMap(const std::map<Key,ValueType> &vars);

    /**
     * Retunrs the number of Variable which have their VariableType equal to
     * @type.
     * */
    std::size_t size( VariableType type);


    /**
     * std container interface stuff. These are standard
     *
     * */

    iterator begin();
    iterator end();
    iterator find(const Key &k);

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    bool empty() const;
    iterator erase(const_iterator it);
    std::size_t erase(const Key &t);
    void clear();
    std::size_t size();


    /***************************************************************************
     * Private
     **************************************************************************/

  private:

    VariablesContainer _vars;


};

/******************************************************************************
 * Implementation
 ******************************************************************************/

/*******************************************************************************
 * Default construction
 *
 * */

template <typename Key, typename ValueType>
Variables<Key,ValueType>::Variables() {
    // Why do I have to write a default constructor which does nothing if I
    // defined constructors with arguments (which cannot take default value) ?
}

/*******************************************************************************
 * Construction from a VariablesContainer
 *
 * */

template <typename Key, typename ValueType>
Variables<Key,ValueType>::Variables(const VariablesContainer &vars)
    : _vars(vars)
{}

/*******************************************************************************
 * Construction from a vector of tuple. The tuple contains the key and
 * (value and VariableType).
 * OtherVarContainer is private.
 *
 * */

template <typename Key, typename ValueType>
Variables<Key,ValueType>::Variables(const OtherVarContainer & vars) {

    for( const auto &i : vars ){

        auto p = _vars.emplace( std::get<0>(i),
                       Variable<ValueType>(std::get<1>(i), std::get<2>(i)));

        if ( !p.second ){

            throw std::logic_error("In construction of Variables : another "
                                       "element with same key already exists");
        }
    }
}

/*******************************************************************************
 * Add a variable @v inside the container with key @k.
 * Returns an iterator to this newly inserted variable.
 *
 * Throws if it was not possible to add this variable with the given key.
 *
 * */

template <typename Key, typename ValueType>
typename Variables<Key,ValueType>::iterator Variables<Key,ValueType>::add
    (const Key &k, const Variable<ValueType>& v) {

    auto p = _vars.emplace( k, v);

    if ( !p.second ){

        throw std::logic_error("adding a new variable to Variables: another "
                                   "element with same key already exists");
    }

    return p.first;
}

/*******************************************************************************
 * Returns a copy of the low lying container
 *
 * */

template <typename Key, typename ValueType>
typename Variables<Key,ValueType>::VariablesContainer
Variables<Key,ValueType>::get() const {

    return _vars;
}

/*******************************************************************************
 * Returns a copy of the Variable contained in the VariablesContainer at
 * key @k.
 *
 * Throws if no element with key @k was found.
 *
 * */

template <typename Key, typename ValueType>
Variable<ValueType> Variables<Key,ValueType>::get(const Key &k) const {

    return _vars.at(k);
}

/*******************************************************************************
 * Returns a vector of const_iterator pointing to the variables of
 * VariableType @type in the container.
 *
 * Returns an empty vector if no variable of type @type was found.
 * */

template <typename K, typename V>
std::vector<typename Variables<K,V>::const_iterator>
Variables<K,V>::get(VariableType type) const {

    std::vector<Variables<K,V>::const_iterator> vec;

    for( auto it = _vars.begin() ; it != _vars.end() ; ++it ){
        if( it->second.getType() == type ){
            vec.push_back(it);
        }
    }

    return vec;
}

/*******************************************************************************
 * Returns a vector of Key (copied) of the variable of VariableType @type
 *
 * */

template <typename K, typename V>
std::vector<K> Variables<K,V>::getKeys(VariableType type) const {
    auto vec = get( type );
    std::vector<K> keys;
    for( auto &i : vec ){
        keys.push_back(i->first);
    }
    return keys;
}

/*******************************************************************************
 * Sets the value @v of a Variable with key @k
 *
 * Throws if the key @k was not found in the container
 *
 * */

template <typename K, typename V>
void Variables<K,V>::set(const K &k, const V &v) {
    auto it = _vars.find(k);
    if( it == _vars.end() ){
        throw std::runtime_error(" -> trying to set a non-existing variable");
    }
    it->second.setValue(v);
}

/*******************************************************************************
 * Call the previous set method for each element of the input vector
 *
 * Throws if a key was not found in the low-lying container
 *
 * */

template <typename K, typename V>
void Variables<K,V>::set(std::vector<std::pair<K,V>> &&val) {
    for( const auto &it : val ){
        set( it.first, it.second);
    }
}

/*******************************************************************************
 * Equivalent to previous set method but for rvalue reference
 *
 * */

template <typename K, typename V>
void Variables<K,V>::set(const std::vector<std::pair<K,V>> &val) {
    for( const auto &it : val ){
        set( it.first, it.second);
    }
}

/*******************************************************************************
 * Sets the current Variables object with another Variables object
 *
 * Throw if a key of the input object is not already defined in the
 * current Variables object
 *
 * */

template <typename K, typename V>
void Variables<K,V>::setFromVariables(Variables<K,V> vars ){
    for( const auto &i : vars ){
        auto iter = _vars.find(i.first);
        if ( iter == _vars.end()){
            throw std::runtime_error("Setting variables from a map : "
                                         "non-existing key");
        }
        if ( iter->second.getType() != i.second.getType() ){
            throw std::runtime_error("Setting variables from a map : "
                                         "VariableType are different");
        }
        iter->second.setValue(i.second.getValue());
    }
}

/*******************************************************************************
 * Sets the current Variables object with a map of Key, value
 *
 * Throw if a key of the input object is not already defined in the
 * current Variables object
 *
 * */

template <typename K, typename V>
void Variables<K,V>::setFromMap(const std::map<K,V> &vars) {
    for( const auto &i : vars ){
        auto iter = _vars.find(i.first) ;
        if ( iter == _vars.end()){
            throw std::runtime_error("Setting variables from a map : "
                                         "non-existing key");
        }
        iter->second.setValue(i.second);
    }
}

/*******************************************************************************
 * Retunrs the number of Variable which have their VariableType equal to
 * @type.
 * */

template <typename K, typename V>
std::size_t Variables<K,V>::size(VariableType type) {
    std::size_t s(0);
    for( auto &i : _vars ){
        if( i.second.getType() == type ){
            ++s;
        }
    }
    return s;
}

/*******************************************************************************
 * std container interface stuff. These are standard
 *
 * */

/*******************************************************************************
 * begin
 * */
template <typename K, typename V>
typename Variables<K,V>::iterator Variables<K,V>::begin() {
    return _vars.begin();
}

/*******************************************************************************
 * end
 * */

template <typename K, typename V>
typename Variables<K,V>::iterator Variables<K,V>::end() {
    return _vars.end();
}

/*******************************************************************************
 * begin (const)
 * */

template <typename K, typename V>
typename Variables<K,V>::const_iterator Variables<K,V>::begin() const{
    return _vars.begin();
}

/*******************************************************************************
 * end (const)
 * */

template <typename K, typename V>
typename Variables<K,V>::const_iterator Variables<K,V>::end() const{
    return _vars.end();
}

/*******************************************************************************
 * find
 * */

template <typename K, typename V>
typename Variables<K,V>::iterator Variables<K,V>::find(const K &k) {
    return _vars.find(k);
}

/*******************************************************************************
 * cbegin
 * */

template <typename K, typename V>
typename Variables<K,V>::const_iterator Variables<K,V>::cbegin() const {
    return _vars.cbegin();
}

/*******************************************************************************
 * cend
 * */

template <typename K, typename V>
typename Variables<K,V>::const_iterator Variables<K,V>::cend() const {
    return _vars.cend();
}

/*******************************************************************************
 * rbegin
 * */

template <typename K, typename V>
typename Variables<K,V>::reverse_iterator Variables<K,V>::rbegin() {
    return _vars.rbegin();
}

/*******************************************************************************
 * rend
 * */

template <typename K, typename V>
typename Variables<K,V>::reverse_iterator Variables<K,V>::rend() {
    return _vars.rend();
}

/*******************************************************************************
 * crbegin
 * */

template <typename K, typename V>
typename Variables<K,V>::const_reverse_iterator Variables<K,V>::crbegin() const {
    return _vars.crbegin();
}

/*******************************************************************************
 * crend
 * */

template <typename K, typename V>
typename Variables<K,V>::const_reverse_iterator Variables<K,V>::crend() const {
    return _vars.crend();
}

/*******************************************************************************
 * empty
 * */

template <typename K, typename V>
bool Variables<K,V>::empty() const {
    return _vars.empty();
}

/*******************************************************************************
 * erase
 * */

template <typename K, typename V>
typename Variables<K,V>::iterator
Variables<K,V>::erase(typename Variables<K,V>::const_iterator it) {
    return _vars.erase(it);
}

/*******************************************************************************
 * erase
 * */

template <typename K, typename V>
std::size_t Variables<K,V>::erase(const K &k){
    return _vars.erase(k);
}

/*******************************************************************************
 * clear
 * */

template <typename K, typename V>
void Variables<K,V>::clear() {
    _vars.clear();
}

/*******************************************************************************
 * size
 * */

template <typename K, typename V>
std::size_t Variables<K,V>::size() {
    return _vars.size();
}



}} // namespace snmpp::math

// Variables.hpp ends here