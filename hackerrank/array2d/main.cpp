#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// https://www.hackerrank.com/challenges/2d-array/problem

#define DEBUG_OUTPUT

using Matrix = std::vector<std::vector<int>>;

std::size_t gl_triplet_size = 3;

namespace {
Matrix getTestCase();
void print(const Matrix& mat, std::ostream& stream = std::cout);
void print(const std::vector<int>& vec, std::ostream& stream = std::cout);
std::vector<int> cumulative_sum(const std::vector<int>& vec);
int hourglassSum(const Matrix& mat);
std::vector<int> column(const Matrix& mat, int index);

}  // namespace

int main() {
  auto test_mat = getTestCase();

#ifdef DEBUG_OUTPUT
  print(test_mat);
#endif

  int maxsum = hourglassSum(test_mat);

  std::cout << "Max sum: " << maxsum << std::endl;

  return 0;
}

namespace {

// ----------------------------------------------------------------------------

std::vector<int> column(const Matrix& mat, int index) {
  std::vector<int> col;
  col.reserve(mat.size());
  for (size_t i = 0; i < mat.size(); ++i) {
    col.push_back(mat[i].at(index));
  }
  return col;
}

// ----------------------------------------------------------------------------

Matrix transpose(const Matrix& mat) {
  Matrix tmat;
  for (size_t icol = 0; icol < mat[0].size(); ++icol) {
    tmat.emplace_back(column(mat, icol));
  }
  return tmat;
}

// ----------------------------------------------------------------------------

Matrix inserted(const Matrix& mat) {
  Matrix insertion;
  insertion.reserve(mat.size() - 2);

  auto begin = std::next(std::begin(mat));
  auto last = std::prev(std::end(mat));
  for (auto it = begin; it != last; ++it) {
    std::vector<int> line;
    line.reserve(it->size());
    for (auto elem = std::next(std::begin(*it)); elem != std::prev(std::end(*it)); ++elem) {
      line.push_back(*elem);
    }
    insertion.push_back(line);
  }
  return insertion;
}

// ----------------------------------------------------------------------------

int hourglassSum(const Matrix& mat) {
  Matrix msum;
  msum.reserve(mat.size());
  for (const auto& line : mat) {
    msum.emplace_back(cumulative_sum(line));
  }

#ifdef DEBUG_OUTPUT
  std::cout << "cum sum matrix: \n";
  print(msum);
#endif

  auto insertion = inserted(mat);

#ifdef DEBUG_OUTPUT
  std::cout << "Lines to be inserted: \n";
  print(insertion);
#endif

  int s = 0;
  int max_sum = std::numeric_limits<int>::min();

  for (size_t il = 0; il < msum.size() - 2; ++il) {
    for (size_t ic = 0; ic < msum[il].size(); ++ic) {
      auto sum = msum[il][ic] + insertion[il][ic] + msum[il + 2][ic];
      if (sum > max_sum) {
        max_sum = sum;
      }
    }
  }
  return max_sum;
}

// ----------------------------------------------------------------------------

std::vector<int> cumulative_sum(const std::vector<int>& vec) {
  std::vector<int> sums;
  auto size = vec.size() - gl_triplet_size + 1;
  sums.reserve(size);
  auto cur = std::begin(vec);
  auto last = std::next(cur, size);

  while (cur != last) {
    auto next = std::next(cur, gl_triplet_size);
    sums.emplace_back(std::accumulate(cur, next, 0));
    ++cur;
  }

  return sums;
}

// ----------------------------------------------------------------------------

Matrix getTestCase() {
  // return {{1, 1, 1, 0, 0, 0},   {0, 1, 0, 0, 0, 0},  {1, 1, 1, 0, 0, 0},
  //         {0, 9, 2, -4, -4, 0}, {0, 0, 0, -2, 0, 0}, {0, 0, -1, -2, -4, 0}};

  return {{1, 1, 1, 0, 0, 0}, {0, 1, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 0},
          {0, 0, 2, 4, 4, 0}, {0, 0, 0, 2, 0, 0}, {0, 0, 1, 2, 4, 0}};
}

// ----------------------------------------------------------------------------

void print(const Matrix& mat, std::ostream& stream) {
  std::cout << " --------- \n";
  for (const auto& l : mat) {
    print(l, stream);
  }
  std::cout << " --------- \n";
}

// ----------------------------------------------------------------------------

void print(const std::vector<int>& vec, std::ostream& stream) {
  for (const auto& e : vec) {
    stream << e << ' ';
  }
  stream << '\n';
}

// ----------------------------------------------------------------------------

}  // namespace
