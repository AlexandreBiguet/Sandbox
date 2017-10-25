//
//  Tools.cpp 
//  snmpp
//
//  Created on 21/10/2017 at 15:08.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>

#include "Tools.hpp"

namespace snmpp { namespace utils {

namespace pt = boost::posix_time;

/*******************************************************************************
 * Returns a string containing the current date in the form :
 * YYYY-Month-DD-H-M-S
 * where Month is e.g. Nov for November
 * */

std::string getCurrentDate(){

    pt::ptime now = pt::second_clock::local_time();

    std::stringstream ss;
    ss<<now.date().year()
      <<"-"<<now.date().month()
      <<"-"<<now.date().day()
      <<"-"<<now.time_of_day().hours()
      <<"-"<<now.time_of_day().minutes()
      <<"-"<<now.time_of_day().seconds();

    return ss.str();
}

/*******************************************************************************
 * Returns a string containing the input string to which a trailing '/' was
 * added if necessary
 * */

std::string addTrailingSlash(const std::string &input) {

    if ( input.empty() ){
        throw std::runtime_error( "addTrailingSlash : empty input string");
    }

    if ( input.back() == '/' ) {
        return input;
    }

    std::string output(input);
    output.push_back('/');
    return output;
}


/*******************************************************************************
 * Creates a directory e.g. non/existent/path/to/dir
 *  throw if the path already exists and is not a directory
 *  throw if impossible to create the directory
 * */

void createDirectory( const std::string &input ){

    boost::filesystem::path p(input);

    if ( boost::filesystem::exists(p)) {

        if( ! boost::filesystem::is_directory(p) ) {
            throw std::runtime_error
                ( "Benchmark : a path with the name '" +input+  "' already "
                    "exist and is not a directory");
        }

    } else {

        boost::system::error_code err;
        if( !boost::filesystem::create_directories(p, err) ) {
            std::string reason(err.message());
            throw std::runtime_error
                ( "Benchmark : Could not create new '" +input + "' directory:"
                    " [" + reason + "]");
        }
    }
}

/**
 * Returns a string containing a human readable time unit
 * Template specification for seconds
 *
 */

template <>
std::string getTimeUnit<std::chrono::seconds>(){
    return "s";
}

/**
 * Returns a string containing a human readable time unit
 * Template specification for milliseconds
 *
 */

template <>
std::string getTimeUnit<std::chrono::milliseconds>() {
    return "ms";
}

/**
 * Returns a string containing a human readable time unit
 * Template specification for microseconds
 *
 */

template <>
std::string getTimeUnit<std::chrono::microseconds>() {
    return "us";
}

/**
 * Returns a string containing a human readable time unit
 * Template specification for nanoseconds
 *
 */

template <>
std::string getTimeUnit<std::chrono::nanoseconds>() {
    return "ns";
}


}} // namespace snmpp::utils


// Tools.cpp ends here