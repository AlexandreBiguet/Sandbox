#include "graph.hpp"
#include "input.hpp"

namespace attparse {

Edge::Edge(const Node::Id& source, const Node::Id& destination) : _src(source), _dest(destination) {}

AdjacencyList::AdjacencyList(const std::vector<Edge>& edges, const std::vector<Node>& nodes) {
  _list.resize(nodes.size());
  for (const auto& e : edges) {
    _list[e._src].push_back(e._dest);
  }
}

bool endOfTag(const std::string& line) {
  if (line.size() < 2) {
    return false;
  }
  return line[0] == '<' && line[1] == '/';
}

AdjacencyList build(const Input& input) {
  std::vector<Edge> edges;
  std::vector<Node> nodes;
  nodes.reserve(input._lines.size() / 2);  // Assumes that the file is written properly

  for (const auto& line : input._lines) {
    if (endOfTag(line)) {
      continue;
    }
    Node n(line);
  }

  return {edges, nodes};
}

}  // namespace attparse
