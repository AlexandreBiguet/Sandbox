cmake_minimum_required(VERSION 3.10)
project(HackerRank LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(array2d array2d/main.cpp)
add_executable(dynamic_array dynamic_array/main.cpp)
add_executable(crush crush/main.cpp)
