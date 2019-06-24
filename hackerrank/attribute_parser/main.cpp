#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.hpp"
#include "input.hpp"

namespace {

attparse::Input constructInput() {
  attparse::Input input;
  input._lines.push_back("<tag1 value = \"Value-1\"> name = \"Name-1\" ");
  input._lines.push_back("<tag2 value = \"Value-2\"> name = \"Name-2\" ");
  input._lines.push_back("</tag2>");
  input._lines.push_back("</tag1>");
  input._lines.push_back("<tag3 value = \"Value-3\"> name = \"Name-3\" ");
  input._lines.push_back("</tag3>");

  input._queries.push_back("tag1~value");
  input._queries.push_back("tag1.tag2~value");
}

std::vector<std::string> parse(const attparse::Input& input);

}  // namespace

int main() {
  attparse::Input in;
  auto v = attparse::parse(in);
  std::copy(std::begin(v), std::end(v), std::ostream_iterator(std::cout, '\n'));
  return 0;
}

namespace {
std::vector<std::string> parse(const Input& input) {
  std::vector<std::string> output;
  output.reserve(input._queries.size());

  auto graph = build(input);

  for (const auto& q : input._queries) {
    output.push_back(attparse::query(graph, q));
  }

  return output;
}

}  // namespace
