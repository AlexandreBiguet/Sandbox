### CMakeLists.txt --- 
## 
## Filename: CMakeLists.txt
## Author: Alexandre BIGUET
## Created: Mer sep 13 21:01:22 2017 (+0200)
## Last-Updated: Mer sep 13 21:56:20 2017 (+0200)
##           By: Alexandre BIGUET
##     Update #: 17
## 
## snmpp
## 

################################################################################
## List of objects
set ( FAKE_OBJ "fake")

################################################################################
## Including sources

add_subdirectory( snmpp )

################################################################################
## Creation of the library

add_library(
  ${PROJECT_LIB}
  SHARED
  $<TARGET_OBJECTS:${FAKE_OBJ}>
  )

set_target_properties(${PROJECT_LIB}
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${SOVERSION} )

target_link_libraries( ${PROJECT_LIB} ${Boost_LIBRARIES})

install( TARGETS ${PROJECT_LIB} LIBRARY DESTINATION ${INSTALL_PATH_LIB} )

################################################################################
## Installation of header files

file( GLOB_RECURSE HEADERS "*.hpp" )
glob_recurse_without_dir( "${HEADERS}" "release" false )
set( HEADERS "${NEW_LIST}" )
install_files_rpath( "${HEADERS}" "${INSTALL_PATH_HEADERS}" "src/" false )




######################################################################
### CMakeLists.txt ends here
