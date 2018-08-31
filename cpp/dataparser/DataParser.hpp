//
//  DataParser.hpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 31/08/2018 at 09:34.
//
#pragma once

#include <string>
#include <vector>
// #include <map>

namespace Sandbox { namespace dataparser {

/// \brief 2d data parser
class DataParser {
 public:
  using Descriptor = std::vector<std::pair<double, double>>;

  explicit DataParser(const std::vector<std::size_t>& cols = {0, 1},
      const std::string& sep = " ");

  Descriptor operator()(const std::string& filename);

 private:
  Descriptor parse();

  /// \brief Discovers the format of the datafile
  /// i.e. (;-separated, or space-separated, ...)
  void discover();

  /// \brief used in the discover method. Checks if another line should be read
  /// \param line : line of file to test
  /// \return true if another line should be read
  bool to_next_line(const std::string& line);

  /// path to the data file
  std::string _datafile;

  /// the data are represented by colunm in the data file.
  /// Since the DataDescriptor is a vector of pair (x, y), the wanted column
  /// are the one used to represent the X and Y cols.
  std::vector<std::size_t> _wantedCols;

  /// By default the separator are spaces. The discover method aims to
  /// discover the separator
  std::string _separator;
};



}}

// DataParser.hpp ends here