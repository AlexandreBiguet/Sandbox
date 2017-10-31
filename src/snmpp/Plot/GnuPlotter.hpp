//
//  GnuPlotter.hpp 
//  snmpp
//
//  Created on 30/10/2017 at 22:24.
//  Copyright Alexandre Biguet © 2017. All rights reserved.
//  Distributed under the MIT Licence
//
#pragma once

/******************************************************************************
 * Description: 
 * ------------
 * Inherits from PlotterBase<Formatter> class with
 * Formatter = StandardFormatter
 *
 * Override the writeDataFiles such that plot can be done with gnuplot
 *
 * The directory tree has the form :
 *   path/to/plot-dir/functionName
 *          /[date]-data (contains the data files .txt)
 *          /[date]-scripts/ (list of .gnu files)
 *          /[date]-plot.sh (script to execute gnuplot)
 *          /[date]-plot/ (contains plots in pdf format)
 *          /[date]-config.txt
 ******************************************************************************/

/******************************************************************************
 * Possible enhancements:
 * ----------------------
 ******************************************************************************/

#include <snmpp/Utils/FormattedOutput.hpp>

#include "Formatter.hpp"
#include "PlotterBase.hpp"

namespace snmpp { namespace plot {

class GnuPlotter : public PlotterBase<StandardFormatter> {

    /***************************************************************************
     * Interface
     **************************************************************************/
  public:

    /**
     * Constructor
     * */
    template < typename FuncType >
    GnuPlotter(const Config &config,
               const utils::FormattedOutput &fmt,
               const FuncType &func )
        : PlotterBase<StandardFormatter>(config,StandardFormatter(fmt),func)
    {}

    /**
     * Writes the data files
     * */
    void writeDataFiles( ) override;


    /**
     * Sets the number of points to be taken for every running variable
     * */
    void setRunningNumberPoints(std::size_t n);

    /***************************************************************************
     * Private
     **************************************************************************/
  private:

    /**
     * Number of points to be taken for the running variables to construct
     * the data file
     * */
    std::size_t _nRunning;

    /**
     * path to the data directory
     * */
    std::string _dataDir;

    /**
     * path to gnuplot scripts directory
     * */
    std::string _scriptsDir;

    /**
     * Writes the config files
     * */
    void writeConfigFile();

    /**
     *  Creates the directory tree
     *  Returns the name of the config file
     * */
    std::string createDirectoryTree( );

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
    void write1DFunction(const std::string& name, const std::string& run,
                         const std::string& multi);


    /**
     * Writes the 1D data by successive call to write1DFunction method
     * */
    void write1DDatae();
};

} } // namespace snmpp::plot

// GnuPlotter.hpp ends here