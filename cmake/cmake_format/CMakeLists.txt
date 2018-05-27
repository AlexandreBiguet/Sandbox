## Author: Alexandre BIGUET
## Created: 2018/04/23 9:28

cmake_minimum_required (VERSION 3.11.0)

project(CMakeFormat LANGUAGES C CXX VERSION 0.0.1)

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

set( PROJECT_LIB ${PROJECT_NAME} )
set( PROJECT_RELEASE_TYPE "dev" )
set( PROJECT_VERSION "${PROJECT_VERSION}-${PROJECT_RELEASE_TYPE}" )
set( PROJECT_DESCRIPTION "This is a description" )
set( SOVERSION ${PROJECT_VERSION_MAJOR} )

include( GNUInstallDirs )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( INSTALL_PATH_LIB ${CMAKE_INSTALL_FULL_LIBDIR} )
set ( INSTALL_PATH_BIN ${CMAKE_INSTALL_FULL_BINDIR} )
set ( INSTALL_PATH_HEADERS ${CMAKE_INSTALL_FULL_INCLUDEDIR} )
set ( INSTALL_PATH_CONFIG ${CMAKE_INSTALL_FULL_SYSCONFDIR} )
set(RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
 set( CMAKE_INSTALL_NAME_DIR ${RPATH})
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
 set(CMAKE_INSTALL_RPATH ${RPATH}:${CMAKE_INSTALL_RPATH})
else ()
  message(FATAL_ERROR "We do not know how to handle RPATH for your system: ${CMAKE_SYSTEM_NAME}")
endif()

set ( CMAKE_CXX_STANDARD 14)

add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(
        Boost 1.64
        COMPONENTS
        coroutine
        graph
        filesystem
        log
        system
        thread
        REQUIRED)

set ( RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

add_subdirectory(src)
