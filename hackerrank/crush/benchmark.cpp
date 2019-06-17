#include <benchmark/benchmark.h>

#include "crush.hpp"

static void BM_arrayManipulation_1(benchmark::State& state) {
  auto n = crush::test_case::array_size();
  auto queries = crush::test_case::queries();
  for (auto _ : state) {
    crush::arrayManipulation_1(n, queries);
  }
}

BENCHMARK(BM_arrayManipulation_1);

static void BM_arrayManipulation_2(benchmark::State& state) {
  auto n = crush::test_case::array_size();
  auto queries = crush::test_case::queries();
  for (auto _ : state) {
    crush::arrayManipulation_2(n, queries);
  }
}

BENCHMARK(BM_arrayManipulation_2);

BENCHMARK_MAIN();
