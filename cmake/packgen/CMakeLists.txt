
cmake_minimum_required(VERSION 3.8.2)
project(packgen LANGUAGES CXX VERSION 0.0.1)

function(package_generator)

  include(GenerateExportHeader)
  include(CMakePackageConfigHelpers)

  set(options VERBOSE)
  set(oneValueArgs
      TARGET_LIBRARY_NAME
      TARGET_LIBRARY_PREFIX_NAME
      TARGETS_NAME
      CMAKE_CONFIG_FILE
      INSTALL_LIBDIR
      INSTALL_BINDIR
      INSTALL_INCLUDEDIR
      INSTALL_SYSCONFDIR
      INSTALL_CMAKECONFDIR
      NAMESPACE)

  cmake_parse_arguments(pg "${options}" "${oneValueArgs}" "" ${ARGN})

  if(${pg_VERBOSE})
    message(STATUS "pg_TARGET_LIBRARY_NAME : ${pg_TARGET_LIBRARY_NAME}")
    message(STATUS "pg_TARGET_LIBRARY_PREFIX_NAME : ${pg_TARGET_LIBRARY_PREFIX_NAME}")
    message(STATUS "pg_TARGETS_NAME : ${pg_TARGETS_NAME}")
    message(STATUS "pg_CMAKE_CONFIG_FILE : ${pg_CMAKE_CONFIG_FILE}")
    message(STATUS "pg_INSTALL_LIBDIR : ${pg_INSTALL_LIBDIR}")
    message(STATUS "pg_INSTALL_BINDIR : ${pg_INSTALL_BINDIR}")
    message(STATUS "pg_INSTALL_INCLUDEDIR : ${pg_INSTALL_INCLUDEDIR}")
    message(STATUS "pg_INSTALL_SYSCONFDIR : ${pg_INSTALL_SYSCONFDIR}")
    message(STATUS "pg_INSTALL_CMAKECONFDIR : ${pg_INSTALL_CMAKECONFDIR}")
  endif()


endfunction()

set(project_lib ${PROJECT_NAME})
set(project_lib_prefix sandbox)
set(project_lib_targets ${project_lib}Targets)

include(GNUInstallDirs)

set(CMAKE_INSTALL_FULL_CMAKECONFDIR ${CMAKE_INSTALL_FULL_LIBDIR}/cmake)

add_library(${project_lib} SHARED packgen/test.cpp)
target_include_directories(
  ${project_lib}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  INTERFACE
  $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/${PROJECT_NAME}>
)

install(DIRECTORY packgen DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hpp")

install(
  TARGETS ${project_lib}
  EXPORT ${project_lib_targets}
  LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR})

package_generator(
  VERBOSE
  TARGET_LIBRARY_NAME ${project_lib}
  TARGET_LIBRARY_PREFIX_NAME ${project_lib_prefix}
  TARGETS_NAME ${project_lib_targets}
  CMAKE_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/packgen-config.cmake.in
  INSTALL_LIBDIR ${CMAKE_INSTALL_FULL_LIBDIR}
  INSTALL_BINDIR ${CMAKE_INSTALL_FULL_BINDIR}
  INSTALL_INCLUDEDIR ${CMAKE_INSTALL_FULL_INCLUDEDIR}
  INSTALL_SYSCONFDIR ${CMAKE_INSTALL_FULL_SYSCONFDIR}
  INSTALL_CMAKECONFDIR ${CMAKE_INSTALL_FULL_CMAKECONFDIR}
  NAMESPACE packgen
)
