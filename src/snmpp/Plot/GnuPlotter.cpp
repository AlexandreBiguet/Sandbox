//
//  GnuPlotter.cpp 
//  snmpp
//
//  Created on 30/10/2017 at 22:29.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

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

    _dataDir = basedir + prefix + "data";
    _scriptsDir = basedir + prefix + "scripts";

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



}

}} // namespace snmpp::plot


// GnuPlotter.cpp ends here