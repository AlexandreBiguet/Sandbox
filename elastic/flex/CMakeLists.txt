cmake_minimum_required(VERSION 3.5.1)

project(ElasticFlex LANGUAGES CXX C VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(flex_rpath)
include(flex_deps)
add_subdirectory(flex)
