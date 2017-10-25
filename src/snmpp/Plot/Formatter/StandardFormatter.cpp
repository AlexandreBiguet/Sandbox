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

    for( const auto &i : val ){
        os << _col << i ;
    }

    os << '\n';
}

}} // namespace snmpp::plot


// StandardFormatter.cpp ends here