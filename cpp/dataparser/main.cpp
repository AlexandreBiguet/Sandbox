//
//  main.cpp 
//  Sandbox
//
//  Created by Alexandre Biguet on 31/08/2018 at 09:30.
//

#include <iostream>

#include <boost/format.hpp>

#include "DataParser.hpp"

void help() {
  std::cout << "dataparser : \n"
            << "Parsing of input datafile which can be created using gen.py \n"
            << "See DataParser class documention for more informations \n";

}

int main(int argc, char ** argv) {

  if (argc < 2) {
    std::cout << "Position argument required : \n"
    << "Usage: dataparser filename [col1 [col2 [...]]]\n\n"
    << "dataparser -h for more informations \n";
    return -1;
  }

  std::string filename(argv[1]);

  if ((filename.find("--help") != std::string::npos) ||
      (filename.find("-h") != std::string::npos )) {
    help();
    return 0;
  }

  std::vector<std::size_t> columns;
  if (argc > 2) {
    for (int i = 2; i < argc; ++i) {
      int c = std::stoi(argv[i]);
      if (c < 0) {
        std::cout << "col. number must be positive \n";
        return -1;
      }
      columns.push_back(static_cast<std::size_t>(c));
    }
  }

  if (columns.empty()) {
    columns.push_back(0);
    columns.push_back(1);
  }

  std::cout << "parsing data file : " << filename << "\n";
  std::cout << "  at columns : ";
  for (const auto& c : columns) {
    std::cout << "[" << c << "] ";
  }
  std::cout << std::endl;

  Sandbox::dataparser::DataParser parser(columns);

  try {

    auto table = parser(filename);

    for (const auto &elem : table) {
      std::cout << boost::format("%10.5f %10.5f \n") % elem.first % elem.second;
    }

  } catch(const std::exception& exception) {
    std::cout << "could not parse data : \n" << exception.what() << std::endl;
  }

  return 0;
}


// main.cpp ends here