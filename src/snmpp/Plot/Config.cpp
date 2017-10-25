//
//  PlotConfig.cpp 
//  snmpp
//
//  Created on 25/10/2017 at 22:51.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//

#include "PlotConfig.hpp"

namespace snmpp { namespace plot {


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

}} // namespace snmpp::plot


// PlotConfig.cpp ends here