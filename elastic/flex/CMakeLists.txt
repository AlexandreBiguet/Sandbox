cmake_minimum_required(VERSION 3.5.1)

project(ElasticFlex LANGUAGES CXX C VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# --- portable install paths

include(GNUInstallDirs)

# -----------------------------------------------------------------------------
# --- Rpath stuff

set(RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
  set(CMAKE_INSTALL_NAME_DIR ${RPATH})
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(CMAKE_INSTALL_RPATH ${RPATH}:${CMAKE_INSTALL_RPATH})
endif()

# -----------------------------------------------------------------------------
# --- Dependencies

set(boost_components program_options system filesystem graph regex coroutine log)
find_package(Boost REQUIRED COMPONENTS ${boost_components})

# -----------------------------------------------------------------------------
# --- source files

# add_subdirectory(msg)
# add_subdirectory(flex)
add_subdirectory(test)
