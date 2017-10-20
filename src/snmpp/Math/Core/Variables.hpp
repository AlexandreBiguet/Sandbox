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

template <typename Key, typename ValueType>
class Variables{

  public:

    using VariablesContainer = std::map<Key, Variable<ValueType>>;
    using iterator = typename VariablesContainer::iterator;
    using const_iterator = typename VariablesContainer::const_iterator;
    using reverse_iterator = typename VariablesContainer::reverse_iterator;
    using const_reverse_iterator =
        typename VariablesContainer::const_reverse_iterator;

  private:

    VariablesContainer _vars;
    using OtherVarContainer = std::vector<std::tuple<Key,ValueType,VariableType>>;

  public:

    Variables();
    explicit Variables(const VariablesContainer &vars);
    explicit Variables(const OtherVarContainer &vars);


    iterator add(const Key &k, const Variable<ValueType> &v);

    VariablesContainer get() const;
    Variable<ValueType> get(const Key &k) const; // may throw
    std::vector< const_iterator > get( VariableType type) const;
    std::vector<Key> getKeys (VariableType type)const;

    void set(const Key &k, const ValueType &v);
    void set(const std::vector<std::pair<Key, ValueType>> &val);
    void set(std::vector<std::pair<Key, ValueType>> &&val);
    void setFromVariables(Variables<Key, ValueType> vars);
    void setFromMap(const std::map<Key,ValueType> &vars);


    /* std container interface stuff */

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
    std::size_t size( VariableType type);

};

/******************************************************************************
 * Implementation
 ******************************************************************************/

template <typename Key, typename ValueType>
Variables<Key,ValueType>::Variables() {
    // Why do I have to write a default constructor which does nothing if I
    // defined constructors with arguments (which cannot take default value) ?
}

template <typename Key, typename ValueType>
Variables<Key,ValueType>::Variables(const VariablesContainer &vars)
    : _vars(vars)
{}


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

template <typename Key, typename ValueType>
typename Variables<Key,ValueType>::VariablesContainer
Variables<Key,ValueType>::get() const {

    return _vars;
}

template <typename Key, typename ValueType>
Variable<ValueType> Variables<Key,ValueType>::get(const Key &k) const {

    return _vars.at(k);
}

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

template <typename K, typename V>
std::vector<K> Variables<K,V>::getKeys(VariableType type) const {
    auto vec = get( type );
    std::vector<K> keys;
    for( auto &i : vec ){
        keys.push_back(i->first);
    }
    return keys;
}

template <typename K, typename V>
void Variables<K,V>::set(const K &k, const V &v) {
    auto it = _vars.find(k);
    if( it == _vars.end() ){
        throw std::runtime_error(" -> trying to set a non-existing variable");
    }
    it->second.setValue(v);
}

template <typename K, typename V>
void Variables<K,V>::set(std::vector<std::pair<K,V>> &&val) {
    for( const auto &it : val ){
        set( it.first, it.second);
    }
}

template <typename K, typename V>
void Variables<K,V>::set(const std::vector<std::pair<K,V>> &val) {
    for( const auto &it : val ){
        set( it.first, it.second);
    }
}

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

template <typename K, typename V>
typename Variables<K,V>::iterator Variables<K,V>::begin() {
    return _vars.begin();
}

template <typename K, typename V>
typename Variables<K,V>::iterator Variables<K,V>::end() {
    return _vars.end();
}

template <typename K, typename V>
typename Variables<K,V>::const_iterator Variables<K,V>::begin() const{
    return _vars.begin();
}

template <typename K, typename V>
typename Variables<K,V>::const_iterator Variables<K,V>::end() const{
    return _vars.end();
}


template <typename K, typename V>
typename Variables<K,V>::iterator Variables<K,V>::find(const K &k) {
    return _vars.find(k);
}


template <typename K, typename V>
typename Variables<K,V>::const_iterator Variables<K,V>::cbegin() const {
    return _vars.cbegin();
}

template <typename K, typename V>
typename Variables<K,V>::const_iterator Variables<K,V>::cend() const {
    return _vars.cend();
}

template <typename K, typename V>
typename Variables<K,V>::reverse_iterator Variables<K,V>::rbegin() {
    return _vars.rbegin();
}

template <typename K, typename V>
typename Variables<K,V>::reverse_iterator Variables<K,V>::rend() {
    return _vars.rend();
}

template <typename K, typename V>
typename Variables<K,V>::const_reverse_iterator Variables<K,V>::crbegin() const {
    return _vars.crbegin();
}

template <typename K, typename V>
typename Variables<K,V>::const_reverse_iterator Variables<K,V>::crend() const {
    return _vars.crend();
}

template <typename K, typename V>
bool Variables<K,V>::empty() const {
    return _vars.empty();
}

template <typename K, typename V>
typename Variables<K,V>::iterator
Variables<K,V>::erase(typename Variables<K,V>::const_iterator it) {
    return _vars.erase(it);
}

template <typename K, typename V>
std::size_t Variables<K,V>::erase(const K &k){
    return _vars.erase(k);
}

template <typename K, typename V>
void Variables<K,V>::clear() {
    _vars.clear();
}

template <typename K, typename V>
std::size_t Variables<K,V>::size() {
    return _vars.size();
}

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


}} // namespace snmpp::math

// Variables.hpp ends here