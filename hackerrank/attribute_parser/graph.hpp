#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace attparse {

class Node {
 public:
  using Id = int;
  Node(const std::string& line);
  const std::string& tagName() const;
  const std::string& value(const std::string& key);
  Id id() const;

 private:
  std::string _tagName;
  std::unordered_map<std::string, std::string> _table;
};

struct Edge {
  Edge(const Node::Id& source, const Node::Id& destination);

  const Node::Id _src;
  const Node::Id _dest;
};

struct AdjacencyList {
  AdjacencyList(const std::vector<Edge>& edges, const std::vector<Node>& nodes);
  std::vector<std::vector<int>> _list;
};

std::string query(const AdjacencyList& graph, const std::string& query);

}  // namespace attparse
