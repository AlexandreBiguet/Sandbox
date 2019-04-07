//
//
//

// test implementing Floyd's algorithm for cycle detection

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

namespace {

/// \brief Generation of a vector containing a repeating sequence of number
/// \param sequence : sequence of number to be repeated
/// \param nrep : number of time to repeat the sequence
/// \return a vector composed of nrep times the input sequence.
///         Its size will be nrep * size(sequence)
std::vector<int> generate_cycle(const std::vector<int> &sequence,
                                std::size_t nrep) {
  const std::size_t nseq = sequence.size();
  std::vector<int> result(nrep * nseq);

  for (size_t i = 0; i < result.size(); i += nseq) {

    size_t index{0};
    auto begin = std::begin(result) + i;
    std::generate(begin, begin + nseq, [&sequence, &index]() {
      const auto &val = sequence[index];
      ++index;
      return val;
    });
  }

  return result;
}

/// \brief Prints a vector
/// \param vec input vector to be printed
void print(const std::vector<int> &vec) {
  std::for_each(std::begin(vec), std::end(vec),
                [](const auto &e) { std::cout << e << " "; });
  std::cout << std::endl;
}

/// \brief Try to find a repeated sequence in the input vector
/// \param vec input vector in which a repeated sequence number is searched
/// \return the sequence of repeated number in vector if found.
///         If no sequence was found, returns an empty vector
/// \note This version of the floyd algorithm only find sequence in input
///       vector that only contain the sequence.
///       E.g this version does not find a sequence in the vector
///       {10, 20, 1, 2, 3, 1, 2, 3}
std::vector<int> access_sequence_floyd_simple(const std::vector<int> &vec) {
  if (vec.size() <= 2) {
    return {};
  }

  auto hare = std::begin(vec);
  auto tortoise = std::begin(vec);

  std::advance(hare, 1);

  while (*hare != *tortoise) {

    if (hare == std::end(vec)) {
      return {}; // no cycle
    }

    std::advance(hare, 1);

    if (hare != std::end(vec)) {
      std::advance(hare, 1);
    }
  }

  std::vector<int> seq(tortoise, hare);

  return seq;
}

/// \brief Performs the floyd algorithm iteration to find a sequence
///        between the two iterators tortoise and hare.
/// \note tortoise and hare must be valid iterators
/// \note tortoise, hare and end must be iterators on the same container
/// \tparam Iter Iterator type that can be advanced
/// \param tortoise
/// \param hare iterator modified by the function. A sequence is found
///        between tortoise and hare
/// \param end iterator pointing to the end of container
/// \return True if a sequence was found in the two input iterators tortoise
///         and hare. False otherwise
template <typename Iter>
bool access_sequence_floyd_iter(Iter tortoise, Iter &hare, Iter end) {
  std::advance(hare, 1);

  while (*hare != *tortoise) {

    if (hare == end) {
      return false;
    }

    std::advance(hare, 1);

    if (hare != end) {
      std::advance(hare, 1);
    }
  }
  return true;
}

/// \brief Check for a repeated sequence of number in input vector
/// \param vec input vector in which a sequence is searched
/// \return a sequence of repeated number in vec. Empty if no such sequence was
///         found.
/// \note This version will find the sequence {1, 2, 3} in the input vector
///        {10, 20, 1, 2, 3, 1, 2, 3}
std::vector<int> access_sequence_floyd(const std::vector<int> &vec) {
  if (vec.size() <= 2) {
    return {};
  }

  auto hare = std::begin(vec);
  auto tortoise = std::begin(vec);

  std::size_t count{0};
  while (!access_sequence_floyd_iter(tortoise, hare, std::end(vec)) &&
         tortoise != std::end(vec)) {
    std::advance(tortoise, 1);
    ++count;
    hare = std::begin(vec) + count;
    if (hare == std::end(vec)) {
      return {};
    }
  }

  if (tortoise == std::end(vec)) {
    return {};
  }

  return std::vector<int>(tortoise, hare);
}

/// \brief
/// \param vec
/// \return
bool check_for_cycle(const std::vector<int> &vec) {
  print(vec);
  auto seq = access_sequence_floyd(vec);
  if (seq.empty()) {
    std::cout << "no cycle in ";
    print(vec);
  } else {
    print(seq);
  }
  std::cout << std::endl;

  return !seq.empty();
}

/// \brief
/// \param v1
/// \param v2
/// \return
std::vector<int> append(const std::vector<int> &v1,
                        const std::vector<int> &v2) {
  std::vector<int> vec;
  vec.reserve(v1.size() + v2.size());
  vec.insert(std::end(vec), std::begin(v1), std::end(v1));
  vec.insert(std::end(vec), std::begin(v2), std::end(v2));
  return vec;
}

} // namespace

int main() {

  if (!check_for_cycle(generate_cycle({1, 2, 3, 5, 6}, 12))) {
    std::cout << "should be circular ... \n";
  }

  if (check_for_cycle({1, 2, 3, 4})) {
    std::cout << "should not be circular ... \n";
  }

  if (check_for_cycle({1, 2, 3, 4, 1, 2})) {
    std::cout << "should not be circular ... \n";
  }

  if (!check_for_cycle(append({10, 20}, generate_cycle({1, 2, 3, 5, 6}, 12)))) {
    std::cout << "should be circular ... \n";
  }

  return 0;
}