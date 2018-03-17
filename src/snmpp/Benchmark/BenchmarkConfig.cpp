//
//  BenchmarkConfig.cpp 
//  snmpp
//
//  Created on 22/10/2017 at 16:28.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include "BenchmarkConfig.hpp"

namespace snmpp { namespace benchmark {

/*******************************************************************************
 * Constructor
 *
 */

BenchmarkConfig::BenchmarkConfig
    (const std::string &funcName,
     const std::string &argName,
     std::size_t iter,
     const std::string &dir)
    : _functionName(funcName), _argumentNames({argName}),
      _iterationNumber(iter), _pathToBenchmarkDir(dir)  {}

/*******************************************************************************
 * Constructor
 *
 */

BenchmarkConfig::BenchmarkConfig
    (const std::string &funcName,
     const std::vector<std::string> &argNames,
     std::size_t iter, const std::string &dir)
    : _functionName(funcName), _argumentNames(argNames),
      _iterationNumber(iter), _pathToBenchmarkDir(dir) {}

/*******************************************************************************
 * return number of iterations
 *
 */

std::size_t BenchmarkConfig::getIterationNumber() const {
    return _iterationNumber;
}


/*******************************************************************************
 * Returns the path to the benchmark directory
 *
 */

std::string BenchmarkConfig::getPathToBenchmarkDir() const {
    return _pathToBenchmarkDir;
}

/*******************************************************************************
 * Returns the function name
 *
 */


std::string BenchmarkConfig::getFunctionName() const{
    return _functionName;
}

/*******************************************************************************
 * Returns a copy of the arguments name
 *
 */


std::vector<std::string> BenchmarkConfig::getArgumentNames() const{
    return _argumentNames;
}

/*******************************************************************************
 * Sets the number of iteration
 *
 */

void BenchmarkConfig::setIterationNumber(std::size_t iter) {
    _iterationNumber = iter;
}

/*******************************************************************************
 * Sets the benchmark directory
 *
 */

void BenchmarkConfig::setPathToBenchmarkDir(const std::string &path) {
    _pathToBenchmarkDir = path;
}

/*******************************************************************************
 * Sets the function name
 *
 */

void BenchmarkConfig::setFunctionName(const std::string &n) {
    _functionName = n;
}

/*******************************************************************************
 * Sets the arguments name
 *
 */

void BenchmarkConfig::setArgumentNames(const std::vector<std::string> &v) {
    _argumentNames = v;
}

}} // namespace snmpp::benchmark


// BenchmarkConfig.cpp ends here