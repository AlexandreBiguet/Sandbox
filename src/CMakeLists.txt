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
set ( UTILS_OBJ "obj_utils")
set ( BENCHMARK_OBJ "obj_benchmark")
set ( MATH_OBJ "obj_math" )

set( OBJECT_LIST
        ${UTILS_OBJ}
        ${MATH_OBJ}
        ${BENCHMARK_OBJ})

################################################################################
## Sources corresponding to object libraries

set( UTILS_SOURCES
        "snmpp/Utils/FormattedOutput.hpp"
        "snmpp/Utils/Sequence.hpp"
        "snmpp/Utils/Tools.cpp"
        "snmpp/Utils/Tools.hpp")

add_library( ${UTILS_OBJ} OBJECT ${UTILS_SOURCES} )


set( BENCHMARK_SOURCES
        "snmpp/Benchmark/BenchmarkConfig.hpp"
        "snmpp/Benchmark/BenchmarkConfig.cpp"
        "snmpp/Benchmark/Benchmark.hpp")

add_library( ${BENCHMARK_OBJ} OBJECT ${BENCHMARK_SOURCES})
set_target_properties( ${BENCHMARK_OBJ}
        PROPERTIES
        INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
        INCLUDE_DIRECTORIES "${CONFILEPATH}")

set( MATH_SOURCES
        "snmpp/Math/Core/FuncBase.hpp"
        "snmpp/Math/Core/Quantity.hpp"
        "snmpp/Math/Core/Variable.hpp"
        "snmpp/Math/Core/Variables.hpp")

add_library( ${MATH_OBJ} OBJECT ${MATH_SOURCES} )


################################################################################
## List of headers that will be installed

set( HEADERS
        "snmpp/Benchmark/BenchmarkConfig.hpp"
        "snmpp/Benchmark/Benchmark.hpp"
        "snmpp/Math/Core/FuncBase.hpp"
        "snmpp/Math/Core/Quantity.hpp"
        "snmpp/Math/Core/Variable.hpp"
        "snmpp/Math/Core/Variables.hpp"
        "snmpp/Utils/FormattedOutput.hpp"
        "snmpp/Utils/Sequence.hpp"
        "snmpp/Utils/Tools.hpp")


################################################################################
## Creation of the library

FillTargetObjectList("${OBJECT_LIST}" TARGET_OBJECTS_LIST)

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
    target_link_libraries( ${PROJECT_LIB} Boost::filesystem)
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

InstallFilesInList( "${HEADERS}" "${INSTALL_PATH_HEADERS}" false)





######################################################################
### CMakeLists.txt ends here
