function(package_generator)

  include(GenerateExportHeader)
  include(CMakePackageConfigHelpers)

  set(options VERBOSE)
  set(oneValueArgs
      EXPORT_NAME
      CONFIG_FILE_NAME
      CMAKE_CONFIG_FILE
      INSTALL_LIBDIR
      INSTALL_BINDIR
      INSTALL_INCLUDEDIR
      INSTALL_SYSCONFDIR
      INSTALL_CMAKECONFDIR
      NAMESPACE)

  cmake_parse_arguments(pg "${options}" "${oneValueArgs}" "" ${ARGN})

  if(${pg_VERBOSE})
    message("----------------------------------------------------")
    message(STATUS "packgen : verbose mode activated")
    message(STATUS "EXPORT_NAME : ${pg_EXPORT_NAME}")
    message(STATUS "CONFIG_FILE_NAME : ${pg_CONFIG_FILE_NAME}")
    message(STATUS "CMAKE_CONFIG_FILE : ${pg_CMAKE_CONFIG_FILE}")
    message(STATUS "INSTALL_LIBDIR : ${pg_INSTALL_LIBDIR}")
    message(STATUS "INSTALL_BINDIR : ${pg_INSTALL_BINDIR}")
    message(STATUS "INSTALL_INCLUDEDIR : ${pg_INSTALL_INCLUDEDIR}")
    message(STATUS "INSTALL_SYSCONFDIR : ${pg_INSTALL_SYSCONFDIR}")
    message(STATUS "INSTALL_CMAKECONFDIR : ${pg_INSTALL_CMAKECONFDIR}")
    message(STATUS "NAMESPACE : ${pg_NAMESPACE}")
  endif()

  set(INCLUDE_INSTALL_DIR "${pg_INSTALL_INCLUDEDIR}")
  set(SYSCONFIG_INSTALL_DIR "${pg_INSTALL_SYSCONFDIR}")
  set(LIB_INSTALL_DIR "${pg_INSTALL_LIBDIR}")

  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${pg_CONFIG_FILE_NAME}/${pg_CONFIG_FILE_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  export(
    EXPORT ${pg_EXPORT_NAME}
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${pg_CONFIG_FILE_NAME}/${pg_CONFIG_FILE_NAME}.cmake"
  )

  configure_package_config_file(
    ${pg_CMAKE_CONFIG_FILE}
    "${CMAKE_CURRENT_BINARY_DIR}/${pg_CONFIG_FILE_NAME}/${pg_CONFIG_FILE_NAME}Config.cmake"
    INSTALL_DESTINATION ${pg_INSTALL_CMAKECONFDIR}
    PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR LIB_INSTALL_DIR
    INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
  )

  install(EXPORT ${pg_EXPORT_NAME}
          FILE ${pg_CONFIG_FILE_NAME}Targets.cmake
          NAMESPACE ${pg_NAMESPACE}
          DESTINATION ${pg_INSTALL_CMAKECONFDIR})

  install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${pg_CONFIG_FILE_NAME}/${pg_CONFIG_FILE_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${pg_CONFIG_FILE_NAME}/${pg_CONFIG_FILE_NAME}ConfigVersion.cmake"
    DESTINATION
    ${pg_INSTALL_CMAKECONFDIR}
    COMPONENT
    Devel
  )

  if(${pg_VERBOSE})
    message("----------------------------------------------------")
  endif()

endfunction()
