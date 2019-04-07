//
//  StandardFormatter.cpp 
//  snmpp
//
//  Created on 25/10/2017 at 23:41.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include "StandardFormatter.hpp"

namespace snmpp { namespace plot {

StandardFormatter::StandardFormatter (const utils::FormattedOutput &col)
    : _col(col){}

void StandardFormatter::write
    (std::ostream &os, const std::vector<double> &val) const {

    for(const auto &i : val) {
        os << _col << i;
    }

    os << '\n';
}

/**
 * write to @os from an input map @in (i.e. the input used to call the
 * function) and an output map @out (i.e. the output of the function's call)
 */

void StandardFormatter::write
    (std::ostream &os, const std::map<std::string,double> &in,
     const std::map<std::string, double> &out){

    for(const auto &i : in) {
        os<< _col << i.second;
    }

    for(const auto &i : out) {
        os<<_col<<i.second;
    }
    os<<'\n';
}


}} // namespace snmpp::plot


// StandardFormatter.cpp ends here