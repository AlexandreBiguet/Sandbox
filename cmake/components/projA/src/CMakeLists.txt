# CMakeLists.txt ---
#
# Filename: CMakeLists.txt Author: Alex BIGUET Created: Wed Apr  5 12:10:23 2017
# (+0200)
#
#

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

set(INCLUDE_INSTALL_DIR "${INSTALL_PATH_HEADERS}")
set(LIB_INSTALL_DIR "${INSTALL_PATH_LIB}")

add_subdirectory(Hello)
add_subdirectory(Hi)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/null.cpp "")

add_library(${PROJECT_LIB} SHARED ${CMAKE_CURRENT_BINARY_DIR}/null.cpp)

set_target_properties(
  ${PROJECT_LIB} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${SOVERSION}
  INTERFACE_${PROJECT_LIB}_MAJOR_VERSION ${SOVERSION}
)

set_property(TARGET ${PROJECT_LIB}
             APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${SOVERSION})

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

target_include_directories(${PROJECT_LIB}
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           INTERFACE
                           $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/${PROJECT_NAME}>
                           )

target_link_libraries(${PROJECT_LIB} PUBLIC Hello Hi)

install(TARGETS ${PROJECT_LIB}
        EXPORT ${PROJECT_LIB_TARGET}
        LIBRARY DESTINATION ${INSTALL_PATH_LIB}
        ARCHIVE DESTINATION ${INSTALL_PATH_LIB}
        RUNTIME DESTINATION ${INSTALL_PATH_BIN}
        INCLUDES DESTINATION ${INSTALL_PATH_HEADERS})

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

export(EXPORT ${PROJECT_LIB_TARGET}
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB_TARGET}.cmake"
       NAMESPACE ${PROJECT_LIB}::
       )

configure_package_config_file(
  "${CMAKE_SOURCE_DIR}/${PROJECT_LIB}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}Config.cmake"
  INSTALL_DESTINATION ${INSTALL_CMAKE_CONFIG}
  PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR
  INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
)

install(EXPORT ${PROJECT_LIB_TARGET}
        FILE
        ${PROJECT_LIB_TARGET}.cmake
        NAMESPACE
        ${PROJECT_LIB}::
        DESTINATION
        ${INSTALL_CMAKE_CONFIG}
        )

install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}ConfigVersion.cmake"
  DESTINATION
  ${INSTALL_CMAKE_CONFIG}
  COMPONENT
  Devel
)

#
# CMakeLists.txt ends here
