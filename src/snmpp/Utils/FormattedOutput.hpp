//
//  FormattedOutput.hpp 
//  snmpp
//
//  Created on 21/10/2017 at 17:32.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * A class for formatted output
 ******************************************************************************/

/******************************************************************************
 * Class Attributes:
 * ----------------- 
 ******************************************************************************/

/******************************************************************************
 * Public Methods: 
 * ---------------
 ******************************************************************************/

/******************************************************************************
 * Private Methods:
 * ----------------
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include <iomanip>

namespace snmpp { namespace utils {

class FormattedOutput {

  private:
    int _width;
    int _precision;

  public:
    FormattedOutput(int width = 15, int precision = 6)
        : _width(width), _precision(precision) {}


    friend std::ostream& operator<<
        ( std::ostream& dest, FormattedOutput const& fmt )
    {
        dest.setf( std::ios_base::fixed, std::ios_base::floatfield );
        dest.setf( std::ios_base::left, std::ios_base::adjustfield );
        dest.precision( fmt._precision );
        dest.width( fmt._width );
        return dest<<std::showpos;
    }

};

}} // namespace snmpp::utils

// FormattedOutput.hpp ends here