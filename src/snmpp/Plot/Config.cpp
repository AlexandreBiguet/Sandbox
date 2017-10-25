//
//  PlotConfig.cpp 
//  snmpp
//
//  Created on 25/10/2017 at 22:51.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//


#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

#include "Config.hpp"
#include <snmpp/Utils/Tools.hpp>

namespace snmpp { namespace plot {

/**
 * Constructor
 *
 * */

Config::Config(const std::string& dir, const std::string& funcName )
    : _pathToPlotDir(dir), _functionName(funcName){

}


/*******************************************************************************
 * Returns the path to the plot directory
 *
 * */

const std::string& Config::getPathToPlotDir() const {
    return _pathToPlotDir;
}

/*******************************************************************************
 * Returns the name of the function to be plotted
 *
 * */

const std::string& Config::getFunctionName() const {
    return _functionName;
}

/*******************************************************************************
 * private method
 *  Create the directory tree
 *
 * */

void Config::createDirectoryTree( ) {

    if ( _prefixWithDate ){
        _date = utils::getCurrentDate();
    }

    std::string prefix(_date);

    std::string basedir = utils::addTrailingSlash(_pathToPlotDir);
    basedir += utils::addTrailingSlash(_functionName);

    utils::createDirectory(basedir);
    utils::createDirectory(basedir + "data");
    utils::createDirectory(basedir + "scripts");
    utils::createDirectory(basedir + "plot");

    toFile(basedir + prefix + "-config.txt");
}

/*******************************************************************************
 * private method
 *  Print the configuration to file
 *
 * */

void Config::toFile( const std::string &path)  {

    boost::filesystem::ofstream ofs(path);

    ofs << "Plot config on " ;

    if ( !_prefixWithDate ){
        _date = utils::getCurrentDate();
    }

    ofs << _date
        << "\n\n"
        << " path to plot dir : "<< _pathToPlotDir << "\n"
        << " function name    : "<<_functionName << "\n\n"
        << " prefixing directories with date : "
        <<std::boolalpha<<_prefixWithDate<<"\n"
        << " date : "<<_date<<"\n";

    ofs.close();

}

}} // namespace snmpp::plot


// PlotConfig.cpp ends here