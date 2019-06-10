cmake_minimum_required(VERSION 3.10)
project(pytorch_cpp_api_example LANGUAGES CXX )

find_package(Torch REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(PATH_TO_MNIST_DATASET ${CMAKE_CURRENT_SOURCE_DIR}/../../datasets)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/config/config.hpp @ONLY)

macro(add_torch_tuto _prefix _src)
  add_executable(${_prefix}_torch_tuto ${_src})
  target_link_libraries(${_prefix}_torch_tuto PRIVATE ${TORCH_LIBRARIES})
  target_include_directories(${_prefix}_torch_tuto PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/config)
endmacro()

add_torch_tuto(example example.cpp)
add_torch_tuto(simple_nn simple_nn.cpp)
