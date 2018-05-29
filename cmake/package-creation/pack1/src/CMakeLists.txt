function(install_files_in_list _list _dest _verbose)

  # test if _dest ends with a '/'
  string(LENGTH "${_dest}" leng)
  math(EXPR begin "${leng}-1")
  string(SUBSTRING "${_dest}" "${begin}" "1" last_char)

  # if ( "${_verbose}" )
  # message( "last char = '${last_char}'" )
  # endif()

  if("${last_char}" STREQUAL "/")

    if("${_verbose}")
      message("in ${_dest} : last char is a '/' ")
    endif()

    string(SUBSTRING "${_dest}" 0 "${begin}" _dest)
  endif()

  foreach(file ${_list})
    get_filename_component(dir ${file} DIRECTORY)
    string(REPLACE "${CMAKE_SOURCE_DIR}/" "" dir "${dir}")

    if("${_verbose}")
      message(" ${file} will be installed to ${_dest}/${dir}")
      message("")
    endif()
    install(FILES ${file} DESTINATION "${_dest}/${dir}" COMPONENT Devel)
  endforeach()
endfunction()

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

set(SOURCES Bonjour/bonjour.cpp Hello/hello.cpp)
set(HEADERS Bonjour/bonjour.hpp Hello/hello.hpp)

# set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(${PROJECT_LIB} SHARED ${SOURCES} ${HEADERS})

set_target_properties(
        ${PROJECT_LIB}
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${SOVERSION}
      INTERFACE_${PROJECT_LIB}_MAJOR_VERSION ${SOVERSION})

set_property(TARGET ${PROJECT_LIB}
  APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${SOVERSION})

install(TARGETS ${PROJECT_LIB}
 EXPORT ${PROJECT_LIB_TARGET}
 LIBRARY DESTINATION ${INSTALL_PATH_LIB}
 ARCHIVE DESTINATION ${INSTALL_PATH_LIB}
 RUNTIME DESTINATION ${INSTALL_PATH_BIN}
 INCLUDES DESTINATION ${INSTALL_PATH_HEADERS}
)

install_files_in_list("${HEADERS}" "${INSTALL_PATH_HEADERS}" false)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT ${PROJECT_LIB_TARGET}
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB_TARGET}.cmake"
  NAMESPACE ${PROJECT_LIB}::
)
configure_file("${CMAKE_SOURCE_DIR}/cmake-config/${PROJECT_LIB}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}Config.cmake"
  @ONLY
)

# set(ConfigPackageLocation ${INSTALL_PATH_LIB}/cmake/${PROJECT_LIB})
set(ConfigPackageLocation ${INSTALL_PATH_LIB}/cmake/)
install(EXPORT ${PROJECT_LIB_TARGET}
  FILE
    ${PROJECT_LIB_TARGET}.cmake
  NAMESPACE
    ${PROJECT_LIB}::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIB}/${PROJECT_LIB}ConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)
