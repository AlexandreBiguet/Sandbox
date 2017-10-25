//
//  PlotConfig.hpp 
//  snmpp
//
//  Created on 25/10/2017 at 22:42.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 ******************************************************************************/

/******************************************************************************
 * Class Attributes:
 * -----------------
 * _pathToPlotDir : Path to the plot directory
 *
 * _functionName : Name of the function to be plotted
 *
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include <string>

namespace snmpp { namespace plot {

class Config {

    /***************************************************************************
     * Interface
     **************************************************************************/

  public:

    /**
     * Returns the path to the plot directory
     *
     * */

    const std::string& getPathToPlotDir() const;

    /**
     * Returns the name of the function to be plotted
     *
     * */
    const std::string& getFunctionName() const;

    /***************************************************************************
     * Private
     **************************************************************************/

  private:

    std::string _pathToPlotDir;
    std::string _functionName;
};

}} // namespace snmpp::plot

// PlotConfig.hpp ends here