## @Author: Alexandre BIGUET
## @Date:   24 - Jun - 2018
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

message(STATUS "Library Name : ${LIBRARY_NAME}")

add_library(${LIBRARY_NAME} SHARED
  myTest/Cool.cpp myTest/Cool.hpp
myTest/Stuff.cpp myTest/Stuff.hpp)

# set_target_properties(
#   ${LIBRARY_NAME} PROPERTIES
#   VERSION ${PROJECT_VERSION}
#   SOVERSION ${PROJECT_VERSION_MAJOR}
#   INTERFACE_${PROJECT_LIB}_MAJOR_VERSION ${SOVERSION}
# )

target_include_directories(
  ${LIBRARY_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${PROJECT_NAME}>
)
