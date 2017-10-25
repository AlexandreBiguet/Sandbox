//
//  PrintfFormatter.cpp 
//  snmpp
//
//  Created on 25/10/2017 at 23:44.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <boost/format.hpp>
#include "PrintfFormatter.hpp"

namespace snmpp { namespace plot {

/**
 * Constructor
 *
 * */
PrintfFormatter::PrintfFormatter(std::string &&fmt) : _fmt(std::move(fmt)) {}

/**
 * write method override
 *
 * */

void PrintfFormatter::write
    (std::ostream &os, const std::vector<double> &val) const {

    for( const auto &i : val ){
        os << boost::format( _fmt ) % i ;
    }

    os << '\n';
}

}} // namespace snmpp


// PrintfFormatter.cpp ends here