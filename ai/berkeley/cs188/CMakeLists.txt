cmake_minimum_required(VERSION 3.10)
project(cs188 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(rpath)
include(ccache)

set(CMAKE_CXX_STANDARD 17)

set(boost_components graph )
find_package(Boost REQUIRED COMPONENTS ${boost_components})

include(GNUInstallDirs)

add_subdirectory(cs)
add_subdirectory(bin)
