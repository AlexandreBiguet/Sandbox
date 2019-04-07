//
//  Tools.hpp 
//  snmpp
//
//  Created on 21/10/2017 at 15:07.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * Small tools
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include <chrono>
#include <string>

namespace snmpp { namespace utils {

/**
 * Returns a string containing the current date in the form :
 * YYYY-Month-DD-H-M-S
 * where Month is e.g. Nov for November
 */

std::string getCurrentDate();

/**
 * Returns a string containing the input string to which a trailing '/' was
 * added if necessary
 */

std::string addTrailingSlash(const std::string &input);


/**
 * Creates a directory e.g. non/existent/path/to/dir
 *  throw if the path already exists and is not a directory
 *  throw if impossible to create the directory
 */

void createDirectory(const std::string &input);

/**
 * Returns a string containing a human readable time unit
 *
 */

template <typename TimeUnit>
std::string getTimeUnit() {
    throw std::logic_error("Not implemented");
}

}} // namespace snmpp::utils

// Tools.hpp ends here