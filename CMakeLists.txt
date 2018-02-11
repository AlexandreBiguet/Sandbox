### CMakeLists.txt ---
##
## Filename: CMakeLists.txt
## Author: Alexandre BIGUET
## Created: Mer sep 13 20:37:41 2017 (+0200)
## Last-Updated: Mer sep 13 21:05:40 2017 (+0200)
##           By: Alexandre BIGUET
##     Update #: 20
##
## snmpp
##

cmake_minimum_required (VERSION 3.5.1)
project( snmpp  LANGUAGES CXX VERSION 0.0.1 )

################################################################################
## Options

option( BUILD_SAMPLES "Build the samples programs"  ON)
option( BUILD_TESTS "Build the tests programs"      ON) ## see comment below
option( BUILD_SANDBOX "Build the sandbox programs"  ON) ## see comment below
option( BUILD_BENCHMARKS "Build benchmark programs" ON)
option( WITH_TESTS "Execution of tests"            OFF) ## Nothing now
option( ENABLE_SHARED "Building shared library"     ON)
option( ENABLE_STATIC "Building static library"    ON)
option( NO_WARNINGS "Build without any additional warnings" OFF )
option( CLANG_WEVERYTHING "Build with -Weverything if compiler accepts it" OFF)

### BUILD_(SANDBOX | TESTS) option is only for tests that I performed. The
### should be useless for user

################################################################################
## Project related declarations
set( PROJECT_LIB ${PROJECT_NAME} )
set( PROJECT_STATIC_LIB "${PROJECT_LIB}-static")
set( PROJECT_RELEASE_TYPE "dev" )
set( PROJECT_VERSION "${PROJECT_VERSION}-${PROJECT_RELEASE_TYPE}" )
set( PROJECT_DESCRIPTION "A simple numerical library in c++" )

set( SOVERSION ${PROJECT_VERSION_MAJOR} )
set( CMAKE_POSITION_INDEPENDENT_CODE ON )
set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )

################################################################################
## Includes
include( CheckCXXCompilerFlag)
include( GNUInstallDirs )
include( "${CMAKE_MODULE_PATH}/utils.cmake" )

################################################################################
## Compilation outputs and installation paths
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( INSTALL_PATH_LIB ${CMAKE_INSTALL_FULL_LIBDIR} )
set ( INSTALL_PATH_BIN ${CMAKE_INSTALL_FULL_BINDIR} )
set ( INSTALL_PATH_HEADERS ${CMAKE_INSTALL_FULL_INCLUDEDIR} )
set ( INSTALL_PATH_CONFIG ${CMAKE_INSTALL_FULL_SYSCONFDIR} )

################################################################################
## rpath stuff
set( CMAKE_INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR} )

################################################################################
## Flags
set ( CMAKE_CXX_STANDARD 11)
SetCompilerFlags()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

################################################################################
## Finding Package config
find_package ( PkgConfig REQUIRED )

################################################################################
## Finding boost
find_package(
        Boost 1.64
        COMPONENTS
        program_options
        filesystem
        system
        thread
        REQUIRED)

include_directories( ${Boost_INCLUDE_DIRS} )
link_directories   ( ${Boost_LIBRARY_DIRS} )

set( DEPENDENCY_LIST "Boost" )

################################################################################
## Configuration files

configure_file( snmpp.pc.in
  "${CMAKE_BINARY_DIR}/lib/pkgconfig/${PROJECT_NAME}.pc" @ONLY )

install( FILES "${CMAKE_BINARY_DIR}/lib/pkgconfig/${PROJECT_NAME}.pc"
  DESTINATION "${INSTALL_PATH_LIB}/pkgconfig")

set( CONFILEPATH "${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}/config" )
configure_file(
        ${CMAKE_SOURCE_DIR}/config.hpp.in
        ${CONFILEPATH}/${PROJECT_NAME}_config.hpp @ONLY)
include_directories(${CONFILEPATH})

################################################################################
## Where the action takes place
add_subdirectory(src)

if( BUILD_SAMPLES )
    add_subdirectory(samples)
endif()

if( BUILD_TESTS )
    add_subdirectory(tests)
endif()

if( BUILD_SANDBOX )
    add_subdirectory(sandbox)
endif()

if( BUILD_BENCHMARKS )
    add_subdirectory(benchmarks)
endif()

################################################################################
## Informations output
PrintPackagesInformation( "${DEPENDENCY_LIST}")
PrintBuildInformations()

######################################################################
### CMakeLists.txt ends here
