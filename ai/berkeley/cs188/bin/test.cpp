#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <numeric>
#include <string>
#include <vector>

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

namespace {

struct Edge {
  using node_type = std::string;
  using weight_type = int;
  node_type _n1, _n2;
  weight_type _w;
};

using EdgeList = std::vector<Edge>;
using Graph = boost::edge_list<EdgeList::iterator>;
using NodeId = std::size_t;

std::set<Edge::node_type> getNodeNames(const EdgeList& edges);
std::vector<NodeId> getNodeIds(const std::set<Edge::node_type>& names);

}  // namespace

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(Edge, _n1, _n2, _w)

int main() {
  std::ifstream stream("/Users/alexandrebiguet/Home/Programs/Alex/Sandbox/ai/berkeley/cs188/bin/data.txt");
  EdgeList edges;

  boost::spirit::istream_iterator f(stream), l;
  bool parse_ok = qi::phrase_parse(f, l, (qi::word >> qi::word >> qi::int_) % qi::eol, qi::blank, edges);

  if (!parse_ok) {
    std::cout << "Parsing graph file failed \n";
    return EXIT_FAILURE;
  }

  Graph g(std::begin(edges), std::end(edges));

  std::cout << "Number of parsed edges: " << boost::num_edges(g) << "\n";

  // for(const auto& edge : boost::graph::)

  return EXIT_SUCCESS;
}

namespace  {

std::set<Edge::node_type> getNodeNames(const EdgeList& edges) {
  std::set<Edge::node_type> s;
  std::for_each(std::begin(edges), std::end(edges), [&s](const auto& edge) {
    s.insert(edge._n1);
    s.insert(edge._n2);
  });
  return s;
}

std::vector<NodeId> getNodeIds(const std::set<Edge::node_type>& names) {
  std::vector<NodeId> ids(names.size());
  std::iota(std::begin(names), std::end(names), 0);
  return ids;
}

}
