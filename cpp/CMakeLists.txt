## Author: Alexandre BIGUET
## Created: 2018/04/23 9:28

cmake_minimum_required (VERSION 3.7.2)

project(Sandbox LANGUAGES C CXX VERSION 0.0.1)

option(BUILD_WITH_CCACHE "Build with CCache" ON)

if(BUILD_WITH_CCACHE)

    if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
        SET(ENV{PATH} /usr/local/opt/ccache/libexec:$ENV{PATH})
    elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        SET(ENV{PATH} /usr/lib/ccache:$ENV{PATH})
    else()
        message(FATAL_ERROR "CCache is not handled for your system: ${CMAKE_SYSTEM_NAME}")
    endif()

    find_program(CCACHE_FOUND ccache)

    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif(CCACHE_FOUND)

endif()

set ( CMAKE_CXX_STANDARD 14)

add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost COMPONENTS
             coroutine
             graph
             filesystem
             log
             system
             thread
             REQUIRED)

set( CONFILEPATH "${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}/config" )
configure_file(
  ${CMAKE_SOURCE_DIR}/config.hpp.in ${CONFILEPATH}/config.hpp @ONLY)
include_directories(${CONFILEPATH})

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" )
set(EXTERNAL_PROJECTS_PREFIX ${CMAKE_BINARY_DIR}/external-projects)
include(ExternalProject)
include("${CMAKE_MODULE_PATH}/install.cmake")

macro(set_output_dir_properties _exec)
    set_target_properties(${_exec} PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
endmacro()

add_subdirectory(std)
add_subdirectory(boost)
add_subdirectory(plugins)
add_subdirectory(geographiclib)
add_subdirectory(nlohmann_json)
add_subdirectory(cppcon)
add_subdirectory(cppnow)
add_subdirectory(dataparser)
add_subdirectory(sort_by_index)
