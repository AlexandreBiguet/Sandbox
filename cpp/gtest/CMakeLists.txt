## @Author: Alexandre BIGUET
## @Date:   24 - Jun - 2018

cmake_minimum_required (VERSION 3.7.2)
# cmake_minimum_required (VERSION 3.10.0)
project(myTest LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" )
set(LIBRARY_NAME ${PROJECT_NAME})

option(MYTEST_CODE_COVERAGE "compute code coverage" ON)

## Using the download project utility make the downloaded project part of
## the current project. The install target installs everything... Which sucks
## in the case of google test
## Note :
## using add_subdirectory (.. EXCLUDE_FROM_ALL) makes this hack useless
# option(INSTALL_GMOCK "This must be off" OFF)
# option(INSTALL_GTEST "This must be off" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# TODO : exclude system files
find_program (iwyu_prg NAMES iwyu)
if(NOT iwyu_prg)
  message(STATUS "Include what you use program : Not Found")
else()
  message(STATUS "Include what you use program : Found")
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE iwyu)
  set(CMAKE_C_INCLUDE_WHAT_YOU_USE iwyu)
endif()
# Creation of the myTest library

# Dl the google test framework
if(${MYTEST_CODE_COVERAGE})
  include(CodeCoverage)
  append_coverage_compiler_flags()
endif()

add_subdirectory(src)
add_subdirectory(test)
