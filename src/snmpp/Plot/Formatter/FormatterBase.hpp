//
//  FormatterBase.hpp 
//  snmpp
//
//  Created on 25/10/2017 at 23:37.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * Base class for formatting classes
 ******************************************************************************/

#include <ostream>
#include <vector>


namespace snmpp { namespace plot {

class FormatterBase {

  public:

    /**
     * Each formatter must implement the write method which takes a vector of
     * value @val and write them to @os
     *
     * */

    virtual void write
        ( std::ostream &os, const std::vector<double> &val) const = 0;
};


}} // namespace snmpp::plot

// FormatterBase.hpp ends here