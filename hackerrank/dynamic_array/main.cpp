#include <iostream>
#include <vector>

// https://www.hackerrank.com/challenges/dynamic-array/problem

using Query = std::vector<int>;

#define DEBUG_OUTPUT

int getN() { return 2; }
int getQ() { return 5; }
std::vector<Query> getQueries() { return {{1, 0, 5}, {1, 1, 7}, {1, 0, 3}, {2, 1, 0}, {2, 1, 1}}; }

int type(const Query& q) { return q[0]; }
bool isType1(const Query& q) { return type(q) == 1; }
int x(const Query& q) { return q[1]; }
int y(const Query& q) { return q[2]; }
void print(const Query& query, std::ostream& stream = std::cout) {
  stream << "[ " << type(query) << " ; " << x(query) << " ; " << y(query) << " ] \n";
}

std::vector<int> dynamic_array(int n, const std::vector<Query>& queries) {
  std::vector<std::vector<int>> sequences;
  sequences.resize(n);
  int last_answer = 0;
  std::vector<int> answers;
  for (const auto& query : queries) {
#ifdef DEBUG_OUTPUT
    print(query);
#endif

    auto seq_idx = (x(query) ^ last_answer) % n;

#ifdef DEBUG_OUTPUT
    std::cout << "Current sequence index: " << seq_idx << std::endl;
#endif

    if (isType1(query)) {
      sequences[seq_idx].push_back(y(query));
    } else {
      last_answer = sequences[seq_idx][y(query) % sequences[seq_idx].size()];

#ifdef DEBUG_OUTPUT
      std::cout << last_answer << std::endl;
#endif
      answers.push_back(last_answer);
    }
  }
  return answers;
}

int main() {
  auto seq_number = getN();
  std::cout << "Number of sequences: " << seq_number << std::endl;

  auto answers = dynamic_array(seq_number, getQueries());

  std::copy(std::begin(answers), std::end(answers), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  return 0;
}
