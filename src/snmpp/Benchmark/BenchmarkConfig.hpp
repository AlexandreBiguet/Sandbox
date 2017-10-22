//
//  BenchmarkConfig.hpp 
//  snmpp
//
//  Created on 22/10/2017 at 16:10.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * Class representing a config for the benchmark class
 ******************************************************************************/

/******************************************************************************
 * Class Attributes:
 * -----------------
 *  _iterationNumber :
 *     A number of time to call the function to be benchmarked with the same
 *     arguments such that a statistical analysis can be done (typically
 *     calcuting mean and variance). Default value is 100.
 *
 * _pathToBenchmarkDir :
 *     The path to the directory where you want the benchmark files to be
 *     written. Default value is defined in snmpp_config.hpp
 *     BENCHMARK_DEFAULT_DIRECTORY_PATH.
 *
 * _functionName :
 *     The human readable name of the function to be benchmarked
 *
 * _argumentNames :
 *     Human readable names of the input argument of the benchmarked function
 ******************************************************************************/

/******************************************************************************
 * Public Methods: 
 * ---------------
 * getters and setters
 ******************************************************************************/

/******************************************************************************
 * Private Methods:
 * ----------------
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include <string>
#include <vector>

#include <snmpp_config.hpp>

namespace snmpp { namespace benchmark {

class BenchmarkConfig {

  private:

    std::string _functionName;
    std::vector<std::string> _argumentNames;
    std::size_t _iterationNumber;
    std::string _pathToBenchmarkDir;

  public:

    explicit BenchmarkConfig
        (const std::string &funcName,
         const std::string &argName,
         std::size_t iter = 100,
         const std::string &dir = "benchmarks" );


    explicit BenchmarkConfig
        (const std::string &funcName,
         const std::vector<std::string> &argNames,
         std::size_t iter = 100,
         const std::string &dir = "benchmarks" );

    std::size_t getIterationNumber() const;
    std::string getPathToBenchmarkDir() const;
    std::string getFunctionName() const;
    std::vector<std::string> getArgumentNames() const;

    void setIterationNumber( std::size_t iter );
    void setPathToBenchmarkDir( const std::string &path);
    void setFunctionName( const std::string &n );
    void setArgumentNames( const std::vector<std::string> &v );



};

}} // namespace snmpp::benchmark

// BenchmarkConfig.hpp ends here