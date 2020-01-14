#include <cstdlib>
#include <exception>
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
// * For this problem we choose to represent the graph as an adjacency list

#define DEBUG_MODE

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

  error_type error_type() const { return _error_type; }

 private:
  enum error_type _error_type;
};

class bad_parsing : public custom_error {
 public:
  explicit bad_parsing() : custom_error(error_type::invalid_input_format, "input parsing error") {}
};

class bad_input : public custom_error {
  // Bit of code duplication with bad_parsing but this structure might change in the future
  // if more error types are introduced
 public:
  explicit bad_input() : custom_error(error_type::invalid_input_format, "input sanity checks failed") {}
};

class internal_error : public std::runtime_error {
 public:
  explicit internal_error(const std::string& reason) : std::runtime_error("internal error : " + reason) {}
};

class duplicate_vertex : public custom_error {
 public:
  duplicate_vertex(const std::string& reason)
      : custom_error(error_type::duplicate_pair, "duplicated vertex" + reason) {}
};

class not_binary : public custom_error {
 public:
  not_binary(const std::string& reason) : custom_error(error_type::not_binary, "graph not binary: " + reason) {}
};

class circular_graph : public custom_error {
 public:
  circular_graph(const std::string& reason) : custom_error(error_type::contains_cycle, "circular graph : " + reason) {}
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

  bool is_binary() const {
    for (size_t i = 0; i < _max_index - 2; ++i) {
      std::size_t sum{0};
      for (size_t j = i + 1; j < _max_index; ++j) {
        sum += _adjacency_matrix[i][j];
        if (sum >= 2) {
          return true;
        }
      }
    }

    return false;
  }

  bool is_cyclic() const { return false; }

  bool is_tree() const { return false; }

  std::string to_string(std::size_t v1, std::size_t v2) {
    std::string str("a--b");
    str.front() = _letters[v1];
    str.back() = _letters[v2];
    return str;
  }

  std::size_t to_index(char c) {
    std::size_t index = _letters.find(c);
    if (index == std::string::npos) {
      // this should have been checked before
      throw internal_error("vertex is not an upper case letter");
    }
    return _letters.find(c);
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
  std::vector<std::vector<int>> _adjacency_matrix;

  const std::string _letters{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  std::size_t _initial_size{26};
  std::size_t _max_index{0};
};

void handle_error(std::exception_ptr error) {
  try {
    std::rethrow_exception(error);
  } catch (const custom_error& except) {
    std::cout << except.what() << " -> " << to_string(except.error_type()) << std::endl;
  } catch (const std::runtime_error& except) {
    std::cout << except.what() << std::endl;
  }
}

}  // namespace

static const std::string USAGE{R"(
tree_of_errors usage:
tree_of_errors space_separated_adjacency_pair
)"};

int main(int argc, char** argv) {
#ifndef DEBUG_MODE
  if (argc != 2) {
    std::cerr << USAGE << std::endl;
    return EXIT_FAILURE;
  }
#endif

  std::string correct_input{"(A,B) (Z,E)"};

  input_sanity_checker checker;

  try {
    checker(correct_input);
  } catch (const bad_input& except) {
    std::cout << except.what() << " -> " << to_string(except.error_type()) << std::endl;
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
    parser(correct_input);
  } catch (...) {
    error = std::current_exception();
  }

  if (error) {
    handle_error(error);
    return EXIT_FAILURE;
  }

  std::cout << graph.to_string_triangle() << std::endl;

  return EXIT_SUCCESS;
}
