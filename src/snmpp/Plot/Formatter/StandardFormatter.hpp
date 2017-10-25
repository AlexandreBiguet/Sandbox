//
//  StandardFormatter.hpp 
//  snmpp
//
//  Created on 25/10/2017 at 23:39.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * A standard formatter which uses utils::FormattedOutput to write the data
 ******************************************************************************/

#include "FormatterBase.hpp"
#include <snmpp/Utils/FormattedOutput.hpp>

namespace snmpp { namespace  plot {

class StandardFormatter : public FormatterBase {

  public:
    explicit StandardFormatter( const utils::FormattedOutput &col );
    void write
        ( std::ostream &os, const std::vector<double> &val) const override ;

  private :
    utils::FormattedOutput _col;
};


}} // namespace snmpp::plot

// StandardFormatter.hpp ends here