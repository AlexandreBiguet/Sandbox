cmake_minimum_required (VERSION 3.5.1)

project (projA LANGUAGES CXX C VERSION 1.0.0)

include(GNUInstallDirs)

set(PROJECT_LIB ${PROJECT_NAME})
set(PROJECT_LIB_TARGET "${PROJECT_LIB}Targets")
set(PROJECT_RELEASE_TYPE "dev")
set(PROJECT_VERSION "${PROJECT_VERSION}-${PROJECT_RELEASE_TYPE}")
set(PROJECT_DESCRIPTION "This is a description")
set(SOVERSION ${PROJECT_VERSION_MAJOR})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(INSTALL_PATH_LIB ${CMAKE_INSTALL_FULL_LIBDIR})
set(INSTALL_PATH_BIN ${CMAKE_INSTALL_FULL_BINDIR})
set(INSTALL_PATH_HEADERS ${CMAKE_INSTALL_FULL_INCLUDEDIR})
set(INSTALL_PATH_CONFIG ${CMAKE_INSTALL_FULL_SYSCONFDIR})
set(INSTALL_CMAKE_CONFIG ${INSTALL_PATH_LIB}/cmake/${PROJECT_LIB})
set(RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
 set(CMAKE_INSTALL_NAME_DIR ${RPATH})
elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
 set(CMAKE_INSTALL_RPATH ${RPATH}:${CMAKE_INSTALL_RPATH})
else ()
  message(FATAL_ERROR "We do not know how to handle RPATH for your system: ${CMAKE_SYSTEM_NAME}")
endif()

set(CMAKE_CXX_STANDARD 14)

find_package(projA REQUIRED)

add_executable(main_all main-all.cpp)
target_link_libraries(main_all projA::projA)
message(STATUS "proja include dirs : ${projA_INCLUDE_DIR}")
target_include_directories(main_all PRIVATE ${projA_INCLUDE_DIR})

# find_package(projA COMPONENTS Hello Hi REQUIRED)
add_executable(main_hello main-hello.cpp)
target_link_libraries(main_hello projA::Hello)
target_include_directories(main_hello PRIVATE ${projA_INCLUDE_DIR})

#
add_executable(main_hi main-hi.cpp)
target_link_libraries(main_hi projA::Hi)
target_include_directories(main_hi PRIVATE ${projA_INCLUDE_DIR})

install(TARGETS main_all DESTINATION ${INSTALL_PATH_BIN})
install(TARGETS main_hello DESTINATION ${INSTALL_PATH_BIN})
install(TARGETS main_hi DESTINATION ${INSTALL_PATH_BIN})
