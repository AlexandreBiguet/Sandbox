//
//  dfs.cpp - interview_prep - Created by Alexandre BIGUET on 28/01/2020.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>

class graph {
 public:
  explicit graph(size_t N) { _adj.resize(N + 1); }

  size_t size() const { return _adj.size(); }

  const std::vector<int>& adjacent(int node) const { return _adj[node]; }

  void add_edge(int n1, int n2) { _adj[n1].push_back(n2); }

  void show() const {
    size_t count{0};
    for (const auto& v: _adj) {
      std::cout << count++ << " --> ";
      for (const auto& e : v) {
        std::cout << e << " ";
      }
      std::cout << "\n";
    }
  }

 private:
  using adjcancy_list = std::vector<std::vector<int>>;
  adjcancy_list _adj;
};

template <typename Func>
void dfs_internal(const graph& g, int node, std::vector<bool>& visited, Func func) {
  if (visited[node]) {
    return;
  }
  visited[node] = true;
  func(node);
  for (const auto& n : g.adjacent(node)) {
    dfs_internal(g, n, visited, func);
  }
}

template <typename Func>
void dfs(const graph& g, Func func, int node) {
  std::vector<bool> visited(g.size(), false);
  dfs_internal(g, node, visited, func);
}

template <typename Func>
void bfs(const graph& g, Func func, int node) {
  std::vector<bool> visited(g.size(), false);
  std::queue<int> queue;

  queue.push(node);

  while(not queue.empty()) {

    int s = queue.front();
    queue.pop();

    func(s);

    for(const auto& a: g.adjacent(s)) {

      if (visited[a]) {
        continue;
      }
      visited[a] = true;
      queue.push(a);

    }
  }
}

int main() {
  graph g(5);

  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(2, 5);
  g.add_edge(3, 5);
  g.add_edge(4, 1);

  g.show();
  std::cout << std::endl;

  auto node_printer = [](int node) { std::cout << node << std::endl; };

  dfs(g, node_printer, 1);

  std::cout << std::endl;

  bfs(g, node_printer, 1);



  return EXIT_SUCCESS;
}