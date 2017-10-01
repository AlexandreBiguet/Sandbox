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

set( PROJECT_LIB ${PROJECT_NAME} )

################################################################################
## Options

################################################################################
## Version
set( SOVERSION ${PROJECT_VERSION})

################################################################################
## Compilation outputs
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

################################################################################
## Flags
set ( CMAKE_CXX_STANDARD 11)
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra" )
set ( CMAKE_POSITION_INDEPENDENT_CODE ON)


################################################################################
## Including GNUInstallDirs for definition of CMAKE_INSTALL_<dir>
include ( GNUInstallDirs )
set ( INSTALL_PATH_LIB     ${CMAKE_INSTALL_LIBDIR}       )
set ( INSTALL_PATH_BIN     ${CMAKE_INSTALL_BINDIR}       )
set ( INSTALL_PATH_HEADERS ${CMAKE_INSTALL_INCLUDEDIR}   )
set ( INSTALL_PATH_CONFIG  ${CMAKE_INSTALL_SYSCONFDIR}   )

################################################################################
## Including cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include( "${CMAKE_MODULE_PATH}/utils.cmake" )

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


################################################################################
## Installation of header files and library done in src/CMakeLists.txt
add_subdirectory(src)


################################################################################
## Creation and installation of the package config file
configure_file( snmpp.pc.in
  "${CMAKE_BINARY_DIR}/lib/pkgconfig/${PROJECT_NAME}.pc" @ONLY )

install( FILES "${CMAKE_BINARY_DIR}/lib/pkgconfig/${PROJECT_NAME}.pc"
  DESTINATION "${INSTALL_PATH_LIB}/pkgconfig")



######################################################################
### CMakeLists.txt ends here
