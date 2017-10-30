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
 * Configuration for a plot
 *
 * The data are written in a directory dir = @_pathToDirPlot/@_functionName
 *
 * The data inside dir can be prefixed by the date if @_prefixWithDate is true
 ******************************************************************************/

/******************************************************************************
 * Class Attributes:
 * -----------------
 * _pathToPlotDir : (string) Path to the plot directory
 *
 * _functionName  : (string) Name of the function to be plotted
 *
 * _prefixWithDate : (bool) if true, directories are prefixed with the date
 *
 * _date : (string) the current date
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
     * Constructor
     *
     * */

    explicit Config(const std::string& dir, const std::string& funcName);

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

    /**
     *  Create the directory tree
     *
     * */
    void createDirectoryTree( );


    /***************************************************************************
     * Private
     **************************************************************************/

  private:

    std::string _pathToPlotDir;
    std::string _functionName;
    bool _prefixWithDate;
    std::string _date;

    /**
     * private method
     *  Print the configuration to file
     *
     * */
    void toFile( const std::string &path);
};

}} // namespace snmpp::plot

// PlotConfig.hpp ends here