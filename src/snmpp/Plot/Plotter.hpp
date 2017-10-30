//
//  Plotter.hpp 
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
 * Class Attributes:
 * ----------------- 
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include <map>
#include <vector>

#include <snmpp/Math/Core/FuncBase.hpp>
#include "Config.hpp"

namespace snmpp { namespace plot {

class Config;

template< typename Formatter >
class Plotter {

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
    Plotter(const Config &config,
            const Formatter &fmt,
            const FuncType &func)
        : _config(config), _formatter(fmt),
          _func(std::make_shared<FuncType>(func)) {}


    /**
     * Writes the data
     * */
    void write( );

    /***************************************************************************
     * Private
     **************************************************************************/
  private:

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

    /**
     * Checks if the domain of definition of the running variable is properly
     * set, i.e. it can't be indefinite or empty
     * -> will throw if any of the previous case is fullfilled
     * */
    void checkDefinitionDomain();

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
void Plotter<Formatter>::checkDefinitionDomain() {

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

/******************************************************************************
 * Writes the data
 * */
template < typename Formatter >
void Plotter<Formatter>::write() {

    // If there is no running variables -> throw
    const std::size_t NrunVar =
        _func->getVariables().size(math::VariableType::Running);

    if (  NrunVar == 0 ){
        throw std::logic_error("Plotter: No running variables in the snmpp "
                                   "function in argument");
    }

    checkDefinitionDomain();

    _config.createDirectoryTree();


}


}} // namespace snmpp::plot

// Plotter.hpp ends here