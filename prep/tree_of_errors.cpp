#include <cstdlib>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

// 1) Parsing Input
// 2) Checking Input
// 3) Constructing oriented graph from input
// 4) Checking if Graph is a Tree
// 5) Printing the Tree

// Design notes:
// * The previous split could allow a team to work together on the problem without too much dependency
// * Current design

// Implementation notes:
// * If Boost is allowed in production code, we could use the Boost.Graph library for the graph data structure
// * For this problem we choose to represent the graph as an adjacency matrix

namespace {

class tokenizer {
 public:
  tokenizer(const std::string& str, std::string delimiter) : _stream(str), _delimiter(std::move(delimiter)) {}

  // std::optional<std::string> next();

  std::vector<std::string> all_remaining() {
    std::vector<std::string> tokens;
    while (true) {
      auto tok = next();
      if (tok.empty()) {
        break;
      }
      tokens.push_back(tok);
    }
    return tokens;
  }

  std::string next() {
    if (_delimiter.size() != 1) {
      throw std::runtime_error("This tokenizer is not able to handle multi delimiter right now");
    }

    std::string tmp;
    std::getline(_stream, tmp, _delimiter.front());
    return tmp;
  }

 private:
  std::stringstream _stream;
  const std::string _delimiter;
};

enum class error_type { invalid_input_format, duplicate_pair, not_binary, contains_cycle, multiple_root };

std::string to_string(error_type et) {
  static std::map<error_type, std::string> _converters  //
      {{error_type::invalid_input_format, "E1"},
       {error_type::duplicate_pair, "E2"},
       {error_type::not_binary, "E3"},
       {error_type::contains_cycle, "E4"},
       {error_type::multiple_root, "E5"}};

  return _converters.at(et);
}

class custom_error : public std::runtime_error {
 public:
  custom_error(const error_type type, const std::string& str) : std::runtime_error(str), _error_type(type) {}

  error_type get_error_type() const { return _error_type; }

 private:
  enum error_type _error_type;
};

struct bad_parsing : public custom_error {
  explicit bad_parsing() : custom_error(error_type::invalid_input_format, "input parsing error") {}
};

struct bad_input : public custom_error {
  // Bit of code duplication with bad_parsing but this structure might change in the future
  // if more error types are introduced
  explicit bad_input() : custom_error(error_type::invalid_input_format, "input sanity checks failed") {}
};

struct internal_error : public std::runtime_error {
  explicit internal_error(const std::string& reason) : std::runtime_error("internal error : " + reason) {}
};

struct duplicate_vertex : public custom_error {
  explicit duplicate_vertex(const std::string& reason)
      : custom_error(error_type::duplicate_pair, "duplicated vertex" + reason) {}
};

struct not_binary : public custom_error {
  explicit not_binary() : custom_error(error_type::not_binary, "graph not binary") {}
};

struct circular_graph : public custom_error {
  explicit circular_graph(const std::string& reason = "")
      : custom_error(error_type::contains_cycle, "circular graph " + reason) {}
};

struct multiple_root : public custom_error {
  explicit multiple_root(const std::string& reason)
      : custom_error(error_type::multiple_root, "multiple roots detected " + reason) {}
};

class parser {
 public:
  struct callbacks {
    std::function<void(std::string)> _on_data = nullptr;
    std::function<void(std::exception_ptr)> _on_error = nullptr;
  };

  explicit parser(const callbacks& callbacks) : _callbacks(callbacks) {}

  void operator()(const std::string& str) {
    tokenizer token(str, " ");
    std::exception_ptr error{nullptr};
    for (auto&& pair : token.all_remaining()) {
      if (_callbacks._on_data) {
        try {
          _callbacks._on_data(std::move(pair));
        } catch (...) {
          error = std::current_exception();
        }
      }

      if (error && _callbacks._on_error) {
        _callbacks._on_error(error);
        return;
      }
    }
  }

 private:
  callbacks _callbacks;
};

class input_sanity_checker {
 public:
  input_sanity_checker() = default;

  void operator()(const std::string& str) {
    if (str.empty() || has_trailing_whitespace(str) || has_leading_whitespace(str)) {
      throw bad_input();
    }

    if (not has_correct_syntax(str)) {
      throw bad_input();
    }
  }

 private:
  bool has_trailing_whitespace(const std::string& str) { return str.back() != ')'; }

  bool has_leading_whitespace(const std::string& str) { return str.front() != '('; }

  bool has_correct_syntax(const std::string& str) {
    // check that every ( is ended by a )
    static const std::string opening_chars{"("};
    static const std::string closing_chars{")"};

    auto is_in = [](char c, const std::string& s) {
      // Find c in string once opening & closing string have more than a single element
      return c == s.front();
    };

    std::stack<char> stack;

    for (const auto& c : str) {
      if (is_in(c, opening_chars)) {
        stack.push(c);
      } else {
        if (is_in(c, closing_chars)) {
          if (stack.empty()) {
            return false;
          }

          if (is_in(stack.top(), opening_chars)) {
            // since we only check for ( and ) no need to check if the last
            // opening char corresponds to the current closing char
            stack.pop();
          } else {
            return false;
          }
        }
      }
    }

    return stack.empty();
  }
};

class graph {
  // This is a specific implementation of a graph
  // -------------------------------------------
  // Generalization is possible and would imply:
  //    - template vertex type
  //    - template internal data structure abstraction
  //    - template directed / undirected
  //    - template weighted / unweighted
  //    - Boost.Graph Library provides generalized data structure and algorithms (that can be visited)

  // Since the test has a duration of 48hours I wondered quite a long time if it was expected to give such an
  // implementation. I make the choice not doing so. Mainly because
  //    - 48h is ok to do an implementation, but I don't think it is sufficient for the implementation to be perfect
  //    - If I had to solve this kind of problem in real life I would have a chat with my teammates and bosses to
  //    understand if such an implementation can bring value to other teams in the company and if it is worth taking
  //    time to implement and maintain.

 public:
  graph() {
    // TODO implement an efficient adjacency matrix
    _adjacency_matrix.resize(_initial_size);
    for (auto& v : _adjacency_matrix) {
      v.resize(_initial_size);
      for (auto& e : v) {
        e = 0;
      }
    }
  }

  /// \throws duplicated_edge if the current edge already exists in the graph
  void add_edge(std::size_t v1, std::size_t v2) {
    if (v1 >= _initial_size || v2 >= _initial_size) {
      throw internal_error("vertex name should be upper case letter");
    }

    if (v1 == v2) {
      std::stringstream stream;
      stream << _letters[v1] << " links to itself";
      throw circular_graph(stream.str());
    }

    // not oriented -> triangular matrix (choosing upper right triangle)

    if (v1 > v2) {
      std::swap(v1, v2);
    }

    if (_adjacency_matrix[v1][v2] == 1) {
      throw duplicate_vertex(" (" + to_string(v1, v2) + ")");
    }

    _adjacency_matrix[v1][v2] = 1;

    _max_index = std::max(_max_index, std::max(v1, v2));
  }

  std::string to_string_tree() const {
    if (not is_binary()) {
      throw not_binary();
    }

    auto roots = all_roots();

    if (is_cyclic(roots)) {
      throw circular_graph();
    }

    if (roots.size() > 1) {
      std::stringstream stream;
      for (const auto& root : roots) {
        stream << to_node_name(root) << " ; ";
      }
      throw multiple_root(stream.str());
    }

    return s_exp(roots[0]);
  }

  std::size_t to_index(char c) {
    std::size_t index = _letters.find(c);
    if (index == std::string::npos) {
      // this should have been checked before
      throw internal_error("vertex is not an upper case letter");
    }
    return _letters.find(c);
  }

  std::string to_string_triangle() const {
    std::stringstream stream;
    stream << "   ";
    for (size_t i = 0; i <= _max_index; ++i) {
      stream << std::setw(2) << _letters[i] << " ";
    }
    stream << "\n";
    for (size_t i = 0; i <= _max_index; ++i) {
      stream << _letters[i] << "  ";
      for (size_t j = 0; j <= _max_index; ++j) {
        if (j > i) {
          stream << std::setw(2) << _adjacency_matrix[i][j] << " ";
        } else {
          stream << std::setw(2) << "-"
                 << " ";
        }
      }
      stream << "\n";
    }
    return stream.str();
  }

 private:
  bool is_binary() const {
    // Brute force O(n^2) implementation that uses
    //   - the fact that the matrix is a triangle
    //   - the fact that self linked node are already sorted out
    //
    // Implementation Note:
    // * Another possibility O(n) in space could have been to increment a running sum for each row of the matrix and
    // throw a not_binary exception (Time complexity of this would have been O(1)) I chose not to do that in order to
    // not over-engineer the add_edge method which I would to keep simple. In a team I would have ask for feedback here

    for (std::size_t i = 0; i < _adjacency_matrix.size() - 2; ++i) {
      std::size_t sum{0};
      for (std::size_t j = i + 1; j < _adjacency_matrix[i].size(); ++j) {
        sum += _adjacency_matrix[i][j];
        if (sum > 2) {
          return false;
        }
      }
    }

    return true;
  }

  bool is_cyclic(const std::vector<std::size_t> starting_nodes) const {
    for (const auto& node : starting_nodes) {
      std::vector<bool> visited_nodes(_max_index + 1, false);
      if (is_cyclic_helper(visited_nodes, node)) {
        return true;
      }
    }

    return false;
  }

  bool is_cyclic_helper(std::vector<bool>& visited, std::size_t v) const {
    if (visited[v]) {
      return true;
    }

    visited[v] = true;

    for (auto&& n : neighbour_of(v)) {
      if (is_cyclic_helper(visited, n)) {
        return true;
      }
    }

    return false;
  }

  std::vector<std::size_t> neighbour_of(std::size_t index) const {
    // O(n) implementation due to the fact that the adjacency matrix is a matrix and not a 'smart' matrix

    std::vector<std::size_t> neighbours;

    for (size_t i = index + 1; i < _adjacency_matrix[index].size(); ++i) {
      if (_adjacency_matrix[index][i] == 1) {
        neighbours.push_back(i);
      }
    }

    return neighbours;
  }

  // Access the first root in graph in alphabetical order
  std::size_t alpha_root_node() const {
    // O(n^2) implementation
    for (std::size_t i = 0; i < _adjacency_matrix.size() - 2; ++i) {
      for (std::size_t j = i + 1; j < _adjacency_matrix[i].size(); ++j) {
        if (_adjacency_matrix[i][j] != 0) {
          return i;
        }
      }
    }
    throw internal_error("graph appears to have no node");
  }

  std::vector<std::size_t> all_roots_1() const {
    // Note: because of priority in errors, cycles must be detected in every possibly disconnected part of the graph

    // Single root : if starting from the root and visited all node would leave none unvisited

    std::vector<bool> visited(_max_index + 1, false);

    std::vector<std::size_t> roots;

    auto first_root = alpha_root_node();
    roots.push_back(first_root);

    is_cyclic_helper(visited, first_root);

    // Finding the last visited node connected to the alpha_root_node
    std::size_t index{0};
    for (std::size_t i = 0; i < visited.size(); ++i) {
      if (visited[i]) {
        index = i;
      }
    }

    // starting after this index looking if there are other connected edge

    for (std::size_t i = index + 1; i < _adjacency_matrix.size(); ++i) {
      for (std::size_t j = i + 1; j < _adjacency_matrix[i].size(); ++j) {
        if (_adjacency_matrix[i][j] != 0) {
          roots.push_back(i);
        }
      }
    }

    return roots;
  }

  std::vector<std::size_t> all_roots() const {
    // Note: because of priority in errors, cycles must be detected in every possibly disconnected part of the graph

    // Single root : if starting from the root and visited all node would leave none unvisited

    std::vector<std::size_t> roots;
    auto first_root = alpha_root_node();
    roots.push_back(first_root);

    for (;;) {
      auto next = next_root(roots.back());
      if (next == std::string::npos) {
        break;
      }
      roots.push_back(next);
    }

    return roots;
  }

  std::size_t next_root(const std::size_t node) const {
    std::vector<bool> visited(_max_index + 1, false);
    is_cyclic_helper(visited, node);

    // Finding the last visited node connected to the alpha_root_node
    std::size_t index{0};
    for (std::size_t i = 0; i < visited.size(); ++i) {
      if (visited[i]) {
        index = i;
      }
    }

    // starting after this index looking if there are other connected edge

    for (std::size_t i = index + 1; i < _adjacency_matrix.size(); ++i) {
      for (std::size_t j = i + 1; j < _adjacency_matrix[i].size(); ++j) {
        if (_adjacency_matrix[i][j] != 0) {
          return i;
        }
      }
    }

    return std::string::npos;
  }

  std::string s_exp(std::size_t root) const {
    std::stringstream stream;

    std::vector<std::size_t> next;

    for (std::size_t i = root; i < _adjacency_matrix[root].size(); ++i) {
      if (_adjacency_matrix[root][i] != 0) {
        next.push_back(i);
      }
    }

    stream << "(" << to_node_name(root);

    for (const auto& node : next) {
      stream << s_exp(node);
    }

    stream << ")";

    return stream.str();
  }

  std::string to_string(std::size_t v1, std::size_t v2) {
    std::string str("a--b");
    str.front() = _letters[v1];
    str.back() = _letters[v2];
    return str;
  }

  std::string to_string() const {
    std::stringstream stream;
    stream << "   ";
    for (size_t i = 0; i <= _max_index; ++i) {
      stream << std::setw(2) << _letters[i] << " ";
    }
    stream << "\n";
    for (size_t i = 0; i <= _max_index; ++i) {
      stream << _letters[i] << "  ";
      for (size_t j = 0; j <= _max_index; ++j) {
        stream << std::setw(2) << _adjacency_matrix[i][j] << " ";
      }
      stream << "\n";
    }
    return stream.str();
  }

  std::string to_node_name(std::size_t index) const {
    if (index >= _letters.size()) {
      throw internal_error("index can't be >= " + std::to_string(_letters.size()));
    }
    return std::string{_letters[index]};
  }

 private:
  std::vector<std::vector<int>> _adjacency_matrix;

  const std::string _letters{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  std::size_t _initial_size{26};
  std::size_t _max_index{0};
};

void handle_error(std::exception_ptr error, bool print_message = true) {
  try {
    std::rethrow_exception(error);
  } catch (const custom_error& except) {
    if (print_message) {
      std::cout << except.what() << " -> ";
    }
    std::cout << to_string(except.get_error_type());
  } catch (const std::runtime_error& except) {
    std::cout << except.what() << std::endl;
  }
}

}  // namespace

#define DEBUG_MODE

int main() {
#ifndef DEBUG_MODE

  std::string input_string;
  std::getline(std::cin, input_string);

#endif

#ifdef DEBUG_MODE
  std::string input_string{"(U,P) (O,L) (A,S) (N,O) (S,T) (U,M) (A,N) (S,U) (L,D)"};
  // std::string input_string{"(A,B) (B,C) (E,F) (F,G) (X,Y) (Y,Z)"};
  // std::string input_string{"(A,B) (B,C) (C,E) (E,D) (D,F) (F,G) (A,E)"};
  // std::string input_string{"(C,E) (B,C) (D,E) (D,B)"};
  // std::string input_string{"(A,B) (A,C) (B,D) (E,F) (F,G) (F,H)"};
#endif

  input_sanity_checker checker;

  bool print_error_message = false;

  try {
    checker(input_string);
  } catch (const bad_input& except) {
    if (print_error_message) {
      std::cout << except.what() << " -> ";
    }
    std::cout << to_string(except.get_error_type());
    return EXIT_FAILURE;
  }

  auto is_pair_grammar_ok = [](const std::string& str) {
    return str.size() == 5 && str[0] == '(' && str[2] == ',' && str[4] == ')' && std::isupper(str[1]) &&
           std::isupper(str[3]);
  };

  graph graph;

  parser parser({//
                 ._on_data =
                     [&is_pair_grammar_ok, &graph](std::string str) {  //
                       if (!is_pair_grammar_ok(str)) {
                         throw bad_parsing();
                       }

                       graph.add_edge(graph.to_index(str[1]), graph.to_index(str[3]));

                       // std::cout << str << std::endl;
                     },
                 ._on_error =
                     [](std::exception_ptr error) {
                       if (!error) {
                         return;
                       }
                       std::rethrow_exception(error);
                     }});

  std::exception_ptr error{nullptr};

  try {
    parser(input_string);
  } catch (...) {
    error = std::current_exception();
  }

  if (error) {
    handle_error(error, print_error_message);
    return EXIT_FAILURE;
  }

  try {
    std::cout << graph.to_string_tree() << std::endl;
  } catch (...) {
    error = std::current_exception();
  }

  if (error) {
    handle_error(error, print_error_message);
    return EXIT_FAILURE;
  }

#ifdef DEBUG_MODE
  std::cout << graph.to_string_triangle() << std::endl;
#endif

  return EXIT_SUCCESS;
}
