### utils.cmake ---
##
## Filename: utils.cmake
## Author: Alexandre BIGUET
## Created: Mer sep 13 20:44:23 2017 (+0200)
## Last-Updated: Mer sep 13 20:44:38 2017 (+0200)
##           By: Alexandre BIGUET
##     Update #: 4
##
## snmpp
##

################################################################################
## This functions sets the compiler flags depending on the options given at
## configuration time.

macro (SetCompilerFlags )

    if (NO_WARNINGS AND CLANG_WEVERYTHING )
        message(FATAL_ERROR "NO_WARNINGS and CLANG_EVERYTHING options cannot "
                "be true at the same time")
    endif()

    if (CLANG_WEVERYTHING )

        CHECK_CXX_COMPILER_FLAG(-Weverything COMPILER_SUPPORTS_EVERYTHING )

        if  (COMPILER_SUPPORTS_EVERYTHING )
            set  (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything" )
        endif()

    else()

        if  (NOT NO_WARNINGS )

            CHECK_CXX_COMPILER_FLAG (-W COMPILER_SUPPORTS_W )
            CHECK_CXX_COMPILER_FLAG (-Wall COMPILER_SUPPORTS_WALL )
            CHECK_CXX_COMPILER_FLAG (-Wextra COMPILER_SUPPORTS_WEXTRA )

            if (COMPILER_SUPPORTS_W  )
                set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W")
            endif()

            if (COMPILER_SUPPORTS_WALL )
                set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
            endif()

            if (COMPILER_SUPPORTS_WEXTRA )
                set  (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra" )
            endif()

        endif()

    endif()

endmacro()

################################################################################
## This function creates a list of $<TARGET_OBJECTS:${ojb_i}> from a list of
## target objects #_inputList
## The function creates a TARGET_OBJECT_LIST list at parent scope
macro (FillTargetObjectList _inputList _outputList)

    foreach (obj ${_inputList})
        get_target_property(_type "${obj}" TYPE)

        if (_type STREQUAL "OBJECT_LIBRARY")
            #list (APPEND _list "$<TARGET_OBJECTS:${obj}>")
            list (APPEND ${_outputList} "$<TARGET_OBJECTS:${obj}>")
        else()
            message(FATAL_ERROR
                    "Some object in list is not of type OBJECT_LIBRARIES")
        endif()

    endforeach()

    #set  (TARGET_OBJECTS_LIST ${_list} PARENT_SCOPE )

endmacro()


################################################################################
## This functions prints information about the current build
function (PrintBuildInformations )

    message("\n===============================================================")
    message("Project Name        : ${PROJECT_NAME}")
    message("Project Version     : ${PROJECT_VERSION}")
    message("Project Bin dir     : ${PROJECT_BINARY_DIR}")
    message("Project Source dir  : ${PROJECT_SOURCE_DIR}")
    message("System Name         : ${CMAKE_SYSTEM_NAME}")
    message("System Processor    : ${CMAKE_SYSTEM_PROCESSOR}")

    message("-------------------")
    message("Build Information :")
    message("-------------------")
    message("Install Prefix      : ${CMAKE_INSTALL_PREFIX}")
    message("CC                  : ${CMAKE_C_COMPILER}")
    message("CXX                 : ${CMAKE_CXX_COMPILER}")
    message("CXXFLAGS            : ${CMAKE_CXX_FLAGS}")
    message("CFLAGS              : ${CMAKE_C_FLAGS}")
    message("LDFLAGS             : ${CMAKE_LIBRARY_PATH}")
    message("C compiler          : ${CMAKE_C_COMPILER_ID}")
    message("CXX compiler        : ${CMAKE_CXX_COMPILER_ID}")
    message("CMake Version       : ${CMAKE_VERSION}")
    message("CMake Generator     : ${CMAKE_GENERATOR}")
    message("Shared Linker Flags : ${CMAKE_SHARED_LINKER_FLAGS}")

endfunction()

################################################################################
## This function prints informations about a list of packages #_list
function (PrintPackagesInformation _list )

    message("----------------------")
    message("List of Dependencies :")
    message("----------------------")
    foreach (dep ${_list} )
        message("   * ${dep} : " )
        message("     Include Dirs    : ${${dep}_INCLUDE_DIRS}")
        message("     Library Dirs    : ${${dep}_LIBRARY_DIRS}")
        message("     Librairies      : ${${dep}_LIBRARIES}")
        message("     LDFLAGS         : ${${dep}_LDFLAGS}")
        message("     LDFLAGS (Other) : ${${dep}_LDFLAGS_OTHER}")
        message("     CFLAGS          : ${${dep}_CFLAGS}")
        message("     CFLAGS  (Other) : ${${dep}_CFLAGS_OTHER}")
        message("     Version         : ${${dep}_VERSION}")
        message("     Prefix          : ${${dep}_PREFIX}")
        message("     IncludeDir      : ${${dep}_INCLUDEDIR}")
        message("     LibDir          : ${${dep}_LIBDIR}\n")
    endforeach()


endfunction()

################################################################################
## This function installs the files in _list into _dest
function  (InstallFilesInList _list _dest _verbose)

  ## test if _dest ends with a '/'
  string (LENGTH "${_dest}" leng )
  math (EXPR begin "${leng}-1" )
  string (SUBSTRING "${_dest}" "${begin}" "1" last_char )

  # if  ("${_verbose}" )
  #   message ("last char = '${last_char}'" )
  # endif()

  if  ("${last_char}" STREQUAL "/" )

    if  ("${_verbose}" )
      message ("in ${_dest} : last char is a '/' " )
    endif()

    string (SUBSTRING "${_dest}" 0 "${begin}" _dest )
  endif()

  foreach (file ${_list} )
    get_filename_component (dir ${file} DIRECTORY )
    string (REPLACE "${CMAKE_SOURCE_DIR}/" "" dir "${dir}" )

    if  ("${_verbose}" )
      message (" ${file} will be installed to ${_dest}/${dir}" )
      message ("" )
    endif()
    install (FILES ${file} DESTINATION "${_dest}/${dir}" )
  endforeach()
endfunction()

######################################################################
### utils.cmake ends here
