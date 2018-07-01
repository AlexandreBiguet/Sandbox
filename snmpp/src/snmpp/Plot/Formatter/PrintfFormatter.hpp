//
//  PrintfFormatter.hpp 
//  snmpp
//
//  Created on 25/10/2017 at 23:42.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * A Formatter which uses printf style format for double
 * -> uses boost::format internally
 ******************************************************************************/

#include <string>

#include "FormatterBase.hpp"

namespace snmpp { namespace plot {

class PrintfFormatter : public FormatterBase {

  public:
    PrintfFormatter(std::string &&fmt);
    void write
        (std::ostream &os, const std::vector<double> &val) const override;

  private:
    std::string _fmt;

};


}} // namespace snmpp::plot

// PrintfFormatter.hpp ends here