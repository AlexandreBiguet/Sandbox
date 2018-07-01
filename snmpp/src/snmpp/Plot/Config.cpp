//
//  PlotConfig.cpp 
//  snmpp
//
//  Created on 25/10/2017 at 22:51.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//


#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "Config.hpp"
#include <snmpp/Utils/Tools.hpp>

namespace snmpp { namespace plot {

/**
 * Constructor
 *
 */

Config::Config(const std::string& dir, const std::string& funcName)
    : _pathToPlotDir(dir), _functionName(funcName){

}


/*******************************************************************************
 * Returns the path to the plot directory
 *
 */

const std::string& Config::getPathToPlotDir() const {
    return _pathToPlotDir;
}

/*******************************************************************************
 * Returns the name of the function to be plotted
 *
 */

const std::string& Config::getFunctionName() const {
    return _functionName;
}

/*******************************************************************************
 *  Print the configuration to file
 *
 */

void Config::toFile(const std::string &path)  {

    boost::filesystem::ofstream ofs(path);

    ofs << "Plot config on ";

    if (!_prefixWithDate) {
        _date = utils::getCurrentDate();
    }

    ofs << _date
        << "\n\n"
        << " path to plot dir : "
        <<  boost::filesystem::absolute(_pathToPlotDir) << "\n"
        << " function name    : "<<_functionName << "\n\n"
        << " prefixing directories with date : "
        <<std::boolalpha<<_prefixWithDate<<"\n";

    ofs.close();

}

/*******************************************************************************
 * Uses current date as a prefix for directory and config file
 */
void Config::useCurrentDateAsPrefix(){
    _prefixWithDate = true;
    _date = utils::getCurrentDate();
    _prefix = _date + '-';
}

/**
 * Returns the prefix
 */
const std::string& Config::getPrefix() const{
    return _prefix;
}


}} // namespace snmpp::plot


// PlotConfig.cpp ends here