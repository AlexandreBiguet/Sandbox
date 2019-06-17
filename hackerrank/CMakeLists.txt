cmake_minimum_required(VERSION 3.10)
project(HackerRank LANGUAGES CXX)

option(HackerRank_ENABLE_BENCHARKS "Enable benchmarks" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(HackerRank_ENABLE_BENCHARKS)
    add_definitions(-DENABLE_BENCHMARKS)
    find_package(benchmark REQUIRED)
endif()




add_executable(array2d array2d/main.cpp)
add_executable(dynamic_array dynamic_array/main.cpp)

add_subdirectory(crush)

