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
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include <string>
#include <vector>

#include <snmpp_config.hpp>

namespace snmpp { namespace benchmark {

class BenchmarkConfig {

  public:

    /**
     * Constructor
     *
     * @param funcName
     * @param argName
     * @param iter
     * @param dir
     */
    explicit BenchmarkConfig
        (const std::string &funcName,
         const std::string &argName,
         std::size_t iter = 100,
         const std::string &dir = "benchmarks");

    /**
     * Constructors
     * @param funcName
     * @param argNames
     * @param iter
     * @param dir
     */
    explicit BenchmarkConfig
        (const std::string &funcName,
         const std::vector<std::string> &argNames,
         std::size_t iter = 100,
         const std::string &dir = "benchmarks");

    /**
     * @return number of iterations
     */
    std::size_t getIterationNumber() const;

    /**
     * @return the path to the benchmark directory
     */
    std::string getPathToBenchmarkDir() const;

    /**
     * @return  the function name
     */
    std::string getFunctionName() const;

    /**
     * copy of the arguments name
     */
    std::vector<std::string> getArgumentNames() const;

    /**
     *  Sets the number of iteration
     * @param iter
     */
    void setIterationNumber(std::size_t iter);

    /**
     * Sets the benchmark directory
     * @param path
     */
    void setPathToBenchmarkDir(const std::string &path);

    /**
     * Sets the function name
     * @param n
     */
    void setFunctionName(const std::string &n);

    /**
     *  Sets the arguments name
     * @param v
     */
    void setArgumentNames(const std::vector<std::string> &v);


  private:

    /**
     * The function name
     */
    std::string _functionName;

    /**
     * List of arguments
     */
    std::vector<std::string> _argumentNames;

    /**
     * Number of iterations
     */
    std::size_t _iterationNumber;

    /**
     * path to the benchmark directory
     */
    std::string _pathToBenchmarkDir;

};

}} // namespace snmpp::benchmark

// BenchmarkConfig.hpp ends here