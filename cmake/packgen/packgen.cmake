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
    message("----------------------------------------------------")
    message(STATUS "packgen : verbose mode activated")
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

  set(INCLUDE_INSTALL_DIR "${pg_INSTALL_INCLUDEDIR}")
  set(SYSCONFIG_INSTALL_DIR "${pg_INSTALL_SYSCONFDIR}")
  set(LIB_INSTALL_DIR "${pg_INSTALL_LIBDIR}")

  set(a_first_prefix ${pg_TARGET_LIBRARY_PREFIX_NAME}-${pg_TARGET_LIBRARY_NAME})
  set(a_second_prefix ${pg_TARGET_LIBRARY_PREFIX_NAME}-${pg_TARGETS_NAME})

  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${a_first_prefix}/${a_first_prefix}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  export(
    EXPORT ${pg_TARGETS_NAME}
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${a_first_prefix}/${a_second_prefix}.cmake"
    NAMESPACE ${pg_TARGET_LIBRARY_NAME}::
  )

  configure_package_config_file(${pg_CMAKE_CONFIG_FILE}
    "${CMAKE_CURRENT_BINARY_DIR}/${a_first_prefix}/${a_first_prefix}Config.cmake"
    INSTALL_DESTINATION ${pg_INSTALL_CMAKECONFDIR}
    PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR LIB_INSTALL_DIR
    INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
  )

  install(EXPORT ${pg_TARGETS_NAME}
          FILE ${a_second_prefix}.cmake
          NAMESPACE ${pg_TARGET_LIBRARY_PREFIX_NAME}::
          DESTINATION ${pg_INSTALL_CMAKECONFDIR})

  install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${a_first_prefix}/${a_first_prefix}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${a_first_prefix}/${a_first_prefix}ConfigVersion.cmake"
    DESTINATION
    ${pg_INSTALL_CMAKECONFDIR}
    COMPONENT
    Devel
  )

  if(${pg_VERBOSE})
    message("----------------------------------------------------")
  endif()

endfunction()
