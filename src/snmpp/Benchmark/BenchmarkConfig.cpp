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

BenchmarkConfig::BenchmarkConfig
    (const std::string &funcName,
     const std::string &argName,
     std::size_t iter,
     const std::string &dir )
    : _functionName(funcName), _argumentNames({argName}),
      _iterationNumber(iter), _pathToBenchmarkDir(dir)  {}


BenchmarkConfig::BenchmarkConfig
    (const std::string &funcName,
     const std::vector<std::string> &argNames,
     std::size_t iter, const std::string &dir)
    : _functionName(funcName), _argumentNames(argNames),
      _iterationNumber(iter), _pathToBenchmarkDir(dir) {}

std::size_t BenchmarkConfig::getIterationNumber() const {
    return _iterationNumber;
}

std::string BenchmarkConfig::getPathToBenchmarkDir() const {
    return _pathToBenchmarkDir;
}

std::string BenchmarkConfig::getFunctionName() const{
    return _functionName;
}

std::vector<std::string> BenchmarkConfig::getArgumentNames() const{
    return _argumentNames;
}

void BenchmarkConfig::setIterationNumber(std::size_t iter) {
    _iterationNumber = iter;
}

void BenchmarkConfig::setPathToBenchmarkDir(const std::string &path) {
    _pathToBenchmarkDir = path;
}

void BenchmarkConfig::setFunctionName( const std::string &n ){
    _functionName = n;
}
void BenchmarkConfig::setArgumentNames( const std::vector<std::string> &v ){
    _argumentNames = v;
}

}} // namespace snmpp::benchmark


// BenchmarkConfig.cpp ends here