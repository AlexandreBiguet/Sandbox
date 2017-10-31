//
//  GnuPlotter.cpp 
//  snmpp
//
//  Created on 30/10/2017 at 22:29.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include <iostream>
#include <sstream>

#include <snmpp/Utils/Tools.hpp>

#include "GnuPlotter.hpp"

namespace snmpp { namespace plot {

/*******************************************************************************
 *  Create the directory tree
 *  Returns the name of the config file
 * */

std::string GnuPlotter::createDirectoryTree( ) {

    const std::string& prefix(_config.getPrefix());

    std::string basedir = utils::addTrailingSlash(_config.getPathToPlotDir());
    basedir += utils::addTrailingSlash(_config.getFunctionName());

    _dataDir = basedir + prefix + "data/";
    _scriptsDir = basedir + prefix + "scripts/";

    utils::createDirectory(basedir);
    utils::createDirectory(_dataDir);
    utils::createDirectory(_scriptsDir);
    utils::createDirectory(basedir + prefix + "plot");

    std::string config_file(basedir + prefix + "config.txt");
    _config.toFile(config_file);
    return config_file;
}

/******************************************************************************
 * Writes the config file
 * */

void GnuPlotter::writeConfigFile() {

    // If there is no running variables -> throw
    const std::size_t NrunVar =
        _func->getVariables().size(math::VariableType::Running);

    if (  NrunVar == 0 ){
        throw std::logic_error("Plotter: No running variables in the snmpp "
                                   "function in argument");
    }

    checkDefinitionDomain();

    std::string config_file (createDirectoryTree());

    boost::filesystem::ofstream ofs(config_file,std::ios_base::app);

    ofs<<"\n"
       <<"List of variables :\n";

    utils::FormattedOutput fmt(15,6);

    for( const auto &var : _func->getVariables() ){

        auto interval = var.second.getInterval();
        ofs<<fmt<<var.first<<" "<<"["<<fmt<<interval.lower()<<" : "
           <<fmt<<interval.upper()<<"]"
           <<fmt<< " (" + var.second.typeToString() + ")" <<"\n";

    }

    ofs<<"\n"
       <<"Fixed values for the variables : \n";

    for(const auto &fixed : _fixedValues) {

        ofs<<fmt<<fixed.first<<" = { ";
        for( const auto &val : fixed.second ){
            ofs<<fmt<<val;
        }
        ofs<<"}\n";

    }

    ofs.close();

}

/*******************************************************************************
 * Writes the data files
 * */
void GnuPlotter::writeDataFiles( ){

    writeConfigFile();

    // Set the fixed value of the non-Running variable which were not set by
    // user to their default value (i.e. their value in func->variables)
    const math::Variables& variables = _func->getVariables();

    for (const auto &i: variables ){
        if( _fixedValues[i.first].empty() ){
            _fixedValues[i.first].push_back(variables.getValue(i.first));
        }
    }

    write1DDatae();

}

/**
 * Writes the 1D data by successive call to write1DFunction method
 * */
void GnuPlotter::write1DDatae(){

    const math::Variables& variables = _func->getVariables();

    auto runv = variables.getKeys(math::VariableType::Running);

    for( const auto &run : runv ){

        // run is name of the running variable

        for( const auto &v : variables ){

            if (v.first == run) {
                continue;
            }

            // Name of the multiple fixed variable
            std::string multi (v.first);

            // path to the directory where to put the data
            std::string dir
                (_dataDir + _config.getFunctionName() + "-" + run + "/"
                     + "multi-"+multi + "/");

            utils::createDirectory(dir);

            write1DFunction(dir,run,multi);

        }

    }

}

/**
 * Sets the number of points to be taken for every running variable
 * */
void GnuPlotter::setRunningNumberPoints(std::size_t n) {
    _nRunning = n;
}

/**
 * Writes the data files and gnuplot script files. The 1 dimensional
 * function is plotted against a running variable @run for multiple fixed
 * values of the the @multi variable.
 *
 * @dir   is the name of corresponding directory
 * @run   is the name of the current running variable
 * @multi is the name of the fixed variable. Each of the fixed values are
 * used to write the datae
 *
 * Throw if the size of the output of the function is 0
 * */

void GnuPlotter::write1DFunction
    (const std::string& dir, const std::string&run,
     const std::string& multi){

    const math::Variables& variables = _func->getVariables();

    // Openning the data file

    std::string filename(dir + "test" + ".dat");

    boost::filesystem::ofstream ofs(filename);

    if ( !ofs.is_open() ){
        throw std::runtime_error("Plot : Output data file is not open");
    }

    // Writing some information into the data file

    ofs<<"# Config of the current plot \n"
       <<"# Running variable     : "<<run<<'\n'
       <<"# Multi fixed variable : "<<multi<<'\n'
       <<"#   with values : " ;
    for( const auto &i : _fixedValues[multi]) {
        ofs<<i<<" ";
    }
    ofs<<"\n#\n#"<<" Other fixed variables [value] \n";
    for( const auto & i : variables ){
        if ( !(i.first == run || i.first == multi ) ) {
            ofs<<"# "<<i.first<<" ["<<i.second.getValue()<<" ] \n";
        }
    }
    ofs<<"\n#\n";
    ofs<<"# Col 1 : run   ["<<run<<"] \n"
       <<"# Col 2 : multi ["<<multi<<"] \n"
       <<"# Col 3 : Function ["<<_config.getFunctionName()<<"] \n\n";

    // Writing the datae

    auto interval = variables.get(run).getInterval();

    auto np = static_cast<const double>(_nRunning);
    const double h = (interval.upper() - interval.lower()) / np;

    std::map<std::string, double> input;

    for ( const auto & it : _fixedValues.at(multi) ) {

        input[multi] = it;

        for (std::size_t i = 0; i < _nRunning; ++i) {

            input[run] = interval.lower() + i * h;

            // Ugly...
            auto output = _func->operator()(input);

            if ( output.empty() ) {

                std::stringstream ss;
                ss<<"Function has empty output for input : (run)"
                  <<run<<" ["<<input[run]<<" ] "<<"and multi"<<multi
                  <<" [ "<<input[multi]<<"] ";

                throw std::runtime_error(ss.str());
            }

            _formatter.write(ofs, input, output);
        }
    }

    ofs.close();

}


}} // namespace snmpp::plot


// GnuPlotter.cpp ends here