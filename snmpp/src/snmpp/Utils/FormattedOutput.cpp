//
//  FormattedOutput.cpp 
//  snmpp
//
//  Created on 25/10/2017 at 21:05.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include "FormattedOutput.hpp"

namespace snmpp { namespace utils {

/*******************************************************************************
 * Constructor. Column widht @width and precision for float nb @precision
 *
 */

FormattedOutput::FormattedOutput(int width, int precision)
    : _width(width), _precision(precision){

    assert(_width > 0);
}

/*******************************************************************************
 * Returns the width
 *
 */
int FormattedOutput::getWidth() {
    return _width;
}

/*******************************************************************************
 * Returns the precision
 *
 */
int FormattedOutput::getPrecision() {
    return _precision;
}

/*******************************************************************************
 * Sets the width
 *
 */
void FormattedOutput::setWidth(int n) {
    assert(n > 0);
    _width = n;
}

/*******************************************************************************
 * Sets the precision
 *
 */
void FormattedOutput::setPrecision(int p) {
    _precision = p;
}



}} // namespace snmpp::utils


// FormattedOutput.cpp ends here