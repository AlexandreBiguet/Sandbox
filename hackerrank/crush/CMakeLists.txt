add_executable(crush main.cpp crush.cpp)

if(HackerRank_ENABLE_BENCHARKS)
    add_executable(bench_crush benchmark.cpp crush.cpp)
    target_link_libraries(bench_crush benchmark::benchmark)
endif()