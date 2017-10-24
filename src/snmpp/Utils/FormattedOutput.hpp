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
 *
 ******************************************************************************/


#include <iomanip>
#include <cassert>

namespace snmpp { namespace utils {

class FormattedOutput {

    /***************************************************************************
     * Interface
     **************************************************************************/
  public:

    /**
     * Constructor. Column widht @width and precision for float nb @precision
     *
     * */
    explicit FormattedOutput(int width = 15, int precision = 6)
        : _width(width), _precision(precision) {

        assert(_width > 0);
    }

    /**
     * Overlaoding of << operator
     *
     * */
    friend std::ostream& operator<<
        ( std::ostream& dest, FormattedOutput const& fmt )
    {
        dest.setf( std::ios_base::fixed, std::ios_base::floatfield );
        dest.setf( std::ios_base::left, std::ios_base::adjustfield );
        dest.precision( fmt._precision );
        dest.width( fmt._width );
        return dest<<std::showpos;
    }

    /**
     * Returns the width
     *
     * */
    int getWidth() {
        return _width;
    }

    /**
     * Returns the precision
     *
     * */
    int getPrecision() {
        return _precision;
    }

    /**
     * Sets the width
     *
     * */
    void setWidth( int n ){
        assert(n > 0);
        _width = n;
    }

    /**
     * Sets the precision
     *
     * */
    void setPrecision( int p ){
        _precision = p;
    }

    /***************************************************************************
     * Private
     **************************************************************************/

  private:
    int _width;
    int _precision;

};

}} // namespace snmpp::utils

// FormattedOutput.hpp ends here