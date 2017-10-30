//
//  PlotterBase.hpp
//  snmpp
//
//  Created on 29/10/2017 at 22:06.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * Templated class for plotting function
 ******************************************************************************/


/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include <map>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <snmpp/Math/Core/FuncBase.hpp>
#include "Config.hpp"

namespace snmpp { namespace plot {

class Config;

template< typename Formatter >
class PlotterBase {

    /***************************************************************************
     * Interface
     **************************************************************************/
  public:

    /**
     * Construction from a config, a snmpp::function. The function name is in
     * the config object
     *
     * */
    template <typename FuncType>
    PlotterBase
        (const Config &config,const Formatter &fmt, const FuncType &func)
        : _config(config), _formatter(fmt),
          _func(std::make_shared<FuncType>(func))
    {}

    /**
     * Writes the data files
     * */
    virtual void writeDataFiles( ) = 0;

    /**
     * Add a fixed value @value for the variables @var
     * Throw if this variable is not contained in the Input function variables
     * If the value added is out of the definition domain, this will silently
     * be ignored
     * */
    void addFixedValue( const std::string &var, double value);

    /**
     * Add fixed values contained in @vec for the variable @var
     * Throw if this variable is not contained in the input function variables
     * If the values added are out of the definition domain, this will silently
     * be ignored
     * */
    void addFixedValues( const std::string &var,
                         const std::vector<double> &vec);

    /**
     * Add fixed values contained in @vec for the variable @var
     * Throw if this variable is not contained in the input function variables
     * rvalue reference.
     * If the values added are out of the definition domain, this will silently
     * be ignored
     * */
    void addFixedValues(const std::string &var, std::vector<double> &&vec);

    /**
     * Sets the number @n of fixed values that should be taken in the
     * corresponding definition interval for variable @var
     * Throws if the variable is not contained in the input function variables
     *
     * This sets the corresponding vector of fixed value in the map of fixed
     * values
     * */
    void setFixedValuesNumber(const std::string &var, const std::size_t n);

    /**
     * Checks if the domain of definition of the running variable is properly
     * set, i.e. it can't be indefinite or empty
     * -> will throw if any of the previous case is fullfilled
     * */
    void checkDefinitionDomain();

    /***************************************************************************
     * Protected
     **************************************************************************/
  protected:

    using Key = std::string;

    /**
     * Config
     * */

    Config _config;

    /**
     * The output formatter used when writing to file
     * */
    Formatter _formatter;

    /**
     * map of fixed values for each variables
     * */
    std::map<Key,std::vector<double>> _fixedValues;

    /**
     * Number of fixed variables for each of the variables
     * */
    std::map<Key, std::size_t > _numberOfFixedValues;

    /**
     * A copy of the function to be plotted
     * */
    std::shared_ptr<math::FuncBase> _func;

};

/******************************************************************************
 * Implementation
 ******************************************************************************/

/******************************************************************************
 * Checks if the domain of definition of the running variable is properly
 * set, i.e. it can't be indefinite or empty
 * -> will throw if any of the previous case is fullfilled
 * */
template < typename Formatter >
void PlotterBase<Formatter>::checkDefinitionDomain() {

    auto rvar_vec = _func->getVariables().get(math::VariableType::Running);

    std::exception_ptr errptr(nullptr);


    for ( const auto &i : rvar_vec ){

        auto domain = i->second.getInterval();

        if ( std::isinf(domain.upper()) || std::isinf(domain.lower())) {
            errptr = std::make_exception_ptr(
                std::logic_error("Interval of var ["+i->first+"] is not "
                    "finite") );
            break;
        }

    }

    if ( errptr ){
        std::rethrow_exception(errptr);
    }
}

/**
 * Add a fixed value @value for the variables @var
 * Throw if this variable is not contained in the Input function variables
 * If the value added is out of the definition domain, this will silently
 * be ignored
 * */
template < typename Formatter >
void PlotterBase<Formatter>::addFixedValue
    (const std::string &var, double value){

    if ( ! _func->hasVariable(var) ){
        throw std::runtime_error(" Variable ["+var+"] does not exist");
    }

    _fixedValues[var].push_back(value);
}

/**
 * Add fixed values contained in @vec for the variable @var
 * Throw if this variable is not contained in the input function variables
 * If the values added are out of the definition domain, this will silently
 * be ignored
 * */
template < typename Formatter >
void PlotterBase<Formatter>::addFixedValues
    ( const std::string &var, const std::vector<double> &vec){

    if ( ! _func->hasVariable(var) ){
        throw std::runtime_error(" Variable ["+var+"] does not exist");
    }

    for( const auto &i : vec ) {
        _fixedValues[var].push_back(i);
    }
}

/**
 * Add fixed values contained in @vec for the variable @var
 * Throw if this variable is not contained in the input function variables
 * rvalue reference.
 * If the values added are out of the definition domain, this will silently
 * be ignored
 * */
template < typename Formatter >
void PlotterBase<Formatter>::addFixedValues
    (const std::string &var, std::vector<double> &&vec){

    if ( ! _func->hasVariable(var) ){
        throw std::runtime_error(" Variable ["+var+"] does not exist");
    }

    for( const auto &i : vec ) {
        _fixedValues[var].emplace_back(i);
    }
}

/**
 * Sets the number @n of fixed values that should be taken in the
 * corresponding definition interval for variable @var
 * Throws if the variable is not contained in the input function variables
 *
 * This sets the corresponding vector of fixed value in the map of fixed
 * values
 * */
template < typename Formatter >
void PlotterBase<Formatter>::setFixedValuesNumber
    (const std::string &var, const std::size_t n){

    if ( ! _func->hasVariable(var) ){
        throw std::runtime_error(" Variable ["+var+"] does not exist");
    }

    _numberOfFixedValues[var] = n;
    auto interval = _func->getVariables().find(var)->second.getInterval();

    double h = (interval.upper() - interval.lower()) / (double) n;

    for( std::size_t i = 0 ; i < n ; ++i ){
        _fixedValues[var].push_back( interval.lower() + i * h);
    }
}

}} // namespace snmpp::plot

// PlotterBase.hpp ends here