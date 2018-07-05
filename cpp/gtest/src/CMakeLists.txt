## @Author: Alexandre BIGUET
## @Date:   24 - Jun - 2018
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

message(STATUS "Library Name : ${LIBRARY_NAME}")

set(SOURCES myTest/Cool.cpp myTest/Cool.hpp myTest/Stuff.cpp myTest/Stuff.hpp)

# set_target_properties(
#   ${LIBRARY_NAME} PROPERTIES
#   VERSION ${PROJECT_VERSION}
#   SOVERSION ${PROJECT_VERSION_MAJOR}
#   INTERFACE_${PROJECT_LIB}_MAJOR_VERSION ${SOVERSION}
# )

## Using cppcheck with cmake version >= 3.10.0
if (${CMAKE_VERSION} GREATER_EQUAL 3.10.0)
  find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
  if (CMAKE_CXX_CPPCHECK)
      list(
          APPEND CMAKE_CXX_CPPCHECK
              "--enable=all"
              "--inconclusive"
              "--std=c++14"
              "--force"
              "--inline-suppr"
              "--config-exclude=${CMAKE_BINARY_DIR}/googletest-src"
              "--output-file=${CMAKE_BINARY_DIR}/cppcheck_outputs.txt"
      )
  endif()
else()
  find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
  add_custom_target(
          cppcheck
          COMMAND ${CMAKE_CXX_CPPCHECK}
          --enable=all
          --std=c++14
          --config-exclude=${CMAKE_BINARY_DIR}/googletest-src
          --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)"
          ${SOURCES}
  )
endif()

add_library(${LIBRARY_NAME} SHARED ${SOURCES})


target_include_directories(
  ${LIBRARY_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${PROJECT_NAME}>
)
