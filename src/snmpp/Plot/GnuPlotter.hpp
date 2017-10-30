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
#include "Plotter.hpp"

namespace snmpp { namespace plot {

class GnuPlotter : public Plotter<StandardFormatter> {

    /***************************************************************************
     * Interface
     **************************************************************************/
  public:

    template < typename FuncType >
    GnuPlotter(const Config &config,
               const utils::FormattedOutput &fmt,
               const FuncType &func )
        : Plotter<StandardFormatter>(config,StandardFormatter(fmt),func)
    {}

    /**
     * Writes the data files
     * */
    void writeDataFiles( ) override;


    /***************************************************************************
     * Private
     **************************************************************************/
  private:

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


};

} } // namespace snmpp::plot

// GnuPlotter.hpp ends here