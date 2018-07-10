# CMakeLists.txt ---
#
# Filename: CMakeLists.txt Author: Alex BIGUET Created: Wed Apr  5 12:10:23 2017
# (+0200)
#
# Uavia
#

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

#
# VERSION sources

# set(HEADERS Hello/Hello.hpp Hi/Hi.hpp)
# set(SOURCES Hello/Hello.cpp Hi/Hi.cpp)
# add_library(${PROJECT_LIB} SHARED ${SOURCES} ${HEADERS})

add_library(${PROJECT_LIB}_Hello SHARED Hello/Hello.cpp)
add_library(${PROJECT_LIB}_Hi SHARED Hi/Hi.cpp)

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
                           $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${PROJECT_NAME}>
                           )

install (TARGETS ${PROJECT_LIB}_Hello
        EXPORT ${PROJECT_LIB}_HelloTargets
        LIBRARY DESTINATION ${INSTALL_PATH_LIB}
        COMPONENT Hello)

install (TARGETS ${PROJECT_LIB}_Hi
        EXPORT ${PROJECT_LIB}_HiTargets
        LIBRARY DESTINATION ${INSTALL_PATH_LIB}
        COMPONENT Hi)

target_link_libraries(${PROJECT_LIB} ${PROJECT_LIB}_Hello ${PROJECT_LIB}_Hi)

install(TARGETS ${PROJECT_LIB}
        EXPORT ${PROJECT_LIB_TARGET}
        LIBRARY DESTINATION ${INSTALL_PATH_LIB}
        ARCHIVE DESTINATION ${INSTALL_PATH_LIB}
        RUNTIME DESTINATION ${INSTALL_PATH_BIN}
        INCLUDES DESTINATION ${INSTALL_PATH_HEADERS})


#
# Installation of header files

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

export(EXPORT ${PROJECT_LIB_TARGET}
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB_TARGET}.cmake"
       NAMESPACE ${PROJECT_LIB}::
       )

export(EXPORT ${PROJECT_LIB}_HelloTargets
      FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB_TARGET}.cmake"
      NAMESPACE ${PROJECT_LIB}::
      )

export(EXPORT ${PROJECT_LIB}_HiTargets
     FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB_TARGET}.cmake"
     NAMESPACE ${PROJECT_LIB}::
     )

set(INCLUDE_INSTALL_DIR "${INSTALL_PATH_HEADERS}")
set(SYSCONFIG_INSTALL_DIR "${INSTALL_PATH_CONFIG}")
set(LIB_INSTALL_DIR "${INSTALL_PATH_LIB}")

configure_package_config_file(
  "${CMAKE_SOURCE_DIR}/${PROJECT_LIB}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}Config.cmake"
  INSTALL_DESTINATION ${INSTALL_CMAKE_CONFIG}
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR LIB_INSTALL_DIR
  INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
)

install(EXPORT ${PROJECT_LIB}_HelloTargets
        FILE
        ${PROJECT_LIB_TARGET}.cmake
        NAMESPACE
        ${PROJECT_LIB}::
        DESTINATION
        ${INSTALL_CMAKE_CONFIG}
        )

install(EXPORT ${PROJECT_LIB}_HiTargets
        FILE
        ${PROJECT_LIB_TARGET}.cmake
        NAMESPACE
        ${PROJECT_LIB}::
        DESTINATION
        ${INSTALL_CMAKE_CONFIG}
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

install(
  FILES
  "Hello/Hello.hpp"
  DESTINATION
  ${INSTALL_PATH_HEADERS}/${PROJECT_NAME}/Hello
  COMPONENT
  Devel
)

install(
  FILES
  "Hi/Hi.hpp"
  DESTINATION
  ${INSTALL_PATH_HEADERS}/${PROJECT_NAME}/Hi
  COMPONENT
  Devel
)

#
# CMakeLists.txt ends here
