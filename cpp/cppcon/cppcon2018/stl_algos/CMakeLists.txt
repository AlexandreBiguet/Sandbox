set(_prefix "cppcon2018")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

add_executable(${_prefix}_make_heap make_heap.cpp)
add_executable(${_prefix}_sort sort.cpp)
add_executable(${_prefix}_partition partition.cpp)