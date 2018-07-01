//
//  MultiIter.hpp 
//  snmpp
//
//  Created on 02/11/2017 at 23:12.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * This is the MultiIndex equivalent but with iterator-like types
 * See MultiIndex for more informations
 *
 * Each element must have a ++ operator
 * Operator ++ of element i must be allowed to be called Nmax[i]
 *
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/


#include <vector>

namespace snmpp { namespace tensor {

template< typename T >
class MultiIter {

    /***************************************************************************
     * Interface
     **************************************************************************/

  public:

    /**
     *
     */

    /***************************************************************************
     * Private
     **************************************************************************/

  private:

};

}} // namespace snmpp

// MultiIter.hpp ends here