//
//  DataParser.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 31/08/2018 at 09:34.
//

#include "DataParser.hpp"

#include <fstream>

#include <boost/tokenizer.hpp>

namespace Sandbox { namespace dataparser {

DataParser::DataParser(const std::vector<std::size_t>& cols,
                       const std::string& sep)
                       : _wantedCols(cols), _separator(sep) {}

// ----------------------------------------------------------------------------

DataParser::Descriptor DataParser::operator()(const std::string& filename) {
  _datafile = filename;

  discover();
  return parse();
}

// ----------------------------------------------------------------------------

DataParser::Descriptor DataParser::parse() {
  using tokenizer_type = boost::tokenizer<boost::escaped_list_separator<char>>;
  boost::escaped_list_separator<char> sep("", _separator, "");

  std::ifstream stream(_datafile);

  if (!stream) {
    throw std::runtime_error("internal error : could not open data file");
  }

  std::string line;
  Descriptor data;

  while (std::getline(stream, line)) {
    tokenizer_type tok(line, sep);

    std::vector<std::string> tok_line;

    for (tokenizer_type::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
      tok_line.push_back(*beg);
    }

    size_t Ncol = *std::max_element(_wantedCols.begin(), _wantedCols.end());

    double a = std::stod(tok_line[_wantedCols[0]]);
    double b = std::stod(tok_line[_wantedCols[1]]);

    data.emplace_back(std::make_pair(a, b));
  }

  return data;
}

// ----------------------------------------------------------------------------

void DataParser::discover() {
  _wantedCols.clear();

  std::ifstream stream(_datafile);

  if (!stream) {
    throw std::runtime_error("internal error : cannot open datafile");
  }

  std::string line;

  while (std::getline(stream, line)) {
    if (to_next_line(line)) {
      continue;
    }
    break;
  }

  std::vector<std::string> seps{",", ";"};

  for (const auto& s : seps) {
    if (line.find(s) != std::string::npos) {
      _separator = s;
      break;
    }
  }
}

// ----------------------------------------------------------------------------
static bool starts_with(const std::string& full, const std::string& prefix) {
  return (full.find(prefix) == 0);
}

bool DataParser::to_next_line(const std::string& line) {
  return (starts_with(line, "#") || starts_with(line, "\n"));
}


}
}

// DataParser.cpp ends here