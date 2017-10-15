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
set ( MATH_OBJ "math" )

set( OBJECT_LIST
        ${FAKE_OBJ}
        ${MATH_OBJ})


add_subdirectory( snmpp )

FillTargetObjectList("${OBJECT_LIST}" TARGET_OBJECTS_LIST)

message( "DEBUG -- target object list : ${TARGET_OBJECTS_LIST}")

################################################################################
## Creation of the library

if( ENABLE_SHARED )

    add_library( ${PROJECT_LIB} SHARED ${TARGET_OBJECTS_LIST} )
    target_include_directories(
            ${PROJECT_LIB}
            PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR} )
    set_target_properties(
            ${PROJECT_LIB}
            PROPERTIES
            VERSION ${PROJECT_VERSION}
            SOVERSION ${SOVERSION} )
    target_link_libraries( ${PROJECT_LIB} ${Boost_LIBRARIES})
    install( TARGETS ${PROJECT_LIB} LIBRARY DESTINATION ${INSTALL_PATH_LIB} )

endif()

if( ENABLE_STATIC )

    add_library(${PROJECT_STATIC_LIB} STATIC ${TARGET_OBJECTS_LIST} )
    target_link_libraries( ${PROJECT_STATIC_LIB} ${Boost_LIBRARIES})
    target_include_directories(
            ${PROJECT_STATIC_LIB}
            PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR} )
    install( TARGETS ${PROJECT_STATIC_LIB} DESTINATION ${INSTALL_PATH_LIB} )
endif()

if( NOT ENABLE_STATIC AND NOT ENABLE_SHARED )
    message( FATAL_ERROR "ENABLE_STATIC and ENABLE_SHARED are both off." )
endif()

################################################################################
## Installation of header files

set( HEADERS
        "snmpp/fake/fake.hpp"
        "snmpp/Math/Core/FuncBase.hpp"
        "snmpp/Math/Core/Quantity.hpp"
        "snmpp/Math/Core/Variable.hpp"
        "snmpp/Math/Core/Variables.hpp" )

InstallFilesInList( "${HEADERS}" "${INSTALL_PATH_HEADERS}" true)





######################################################################
### CMakeLists.txt ends here
