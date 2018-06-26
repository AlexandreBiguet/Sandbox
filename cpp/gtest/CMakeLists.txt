## @Author: Alexandre BIGUET
## @Date:   24 - Jun - 2018

cmake_minimum_required (VERSION 3.7.2)
project(myTest LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" )
set(LIBRARY_NAME ${PROJECT_NAME})

# Creation of the myTest library

# Dl the google test framework

add_subdirectory(src)
add_subdirectory(test)