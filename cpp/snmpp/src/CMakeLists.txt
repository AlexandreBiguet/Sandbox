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

# set  (UTILS_OBJ     "obj_utils"    )
# set  (BENCHMARK_OBJ "obj_benchmark")
# set  (MATH_OBJ      "obj_math"     )
# set  (PLOT_OBJ      "obj_plot"     )
# set  (TENSOR_OBJ    "obj_tensor"   )
#
# set (OBJECT_LIST
#         ${UTILS_OBJ}
#         ${MATH_OBJ}
#         ${BENCHMARK_OBJ}
#         ${PLOT_OBJ}
#         ${TENSOR_OBJ})
#
# ################################################################################
# ## Sources corresponding to utils object library
#
# set (UTILS_SOURCES
#         "snmpp/Utils/FormattedOutput.hpp"
#         "snmpp/Utils/FormattedOutput.cpp"
#         "snmpp/Utils/Sequence.hpp"
#         "snmpp/Utils/Tools.cpp"
#         "snmpp/Utils/Tools.hpp")
#
# add_library (${UTILS_OBJ} OBJECT ${UTILS_SOURCES} )
#
# ################################################################################
# ## Sources corresponding to benchmark object library
#
# set (BENCHMARK_SOURCES
#         "snmpp/Benchmark/BenchmarkConfig.hpp"
#         "snmpp/Benchmark/BenchmarkConfig.cpp"
#         "snmpp/Benchmark/Benchmark.hpp")
#
# add_library (${BENCHMARK_OBJ} OBJECT ${BENCHMARK_SOURCES})
# set_target_properties (${BENCHMARK_OBJ}
#         PROPERTIES
#         INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
#         INCLUDE_DIRECTORIES "${CONFILEPATH}")
#
# ################################################################################
# ## Sources corresponding to math object library
#
# set (MATH_SOURCES
#         "snmpp/Math/Core/FuncBase.hpp"
#         "snmpp/Math/Core/Quantity.hpp"
#         "snmpp/Math/Core/Variable.hpp"
#         "snmpp/Math/Core/Variables.hpp")
#
# add_library (${MATH_OBJ} OBJECT ${MATH_SOURCES} )
#
# ################################################################################
# ## Sources corresponding to plot object library
#
# set  (PLOT_SOURCES
#         "snmpp/Plot/Formatter/FormatterBase.hpp"
#         "snmpp/Plot/Formatter/PrintfFormatter.hpp"
#         "snmpp/Plot/Formatter/PrintfFormatter.cpp"
#         "snmpp/Plot/Formatter/StandardFormatter.hpp"
#         "snmpp/Plot/Formatter/StandardFormatter.cpp"
#         "snmpp/Plot/Config.cpp"
#         "snmpp/Plot/Config.hpp"
#         "snmpp/Plot/Formatter.hpp"
#         "snmpp/Plot/GnuPlotter.hpp"
#         "snmpp/Plot/GnuPlotter.cpp"
#         "snmpp/Plot/PlotterBase.hpp"
#         )
#
# add_library (${PLOT_OBJ} OBJECT ${PLOT_SOURCES})
# set_target_properties (${PLOT_OBJ}
#         PROPERTIES
#         INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}" )
#
# ################################################################################
# ## Sources corresponding to tensor object library
# set (TENSOR_SOURCES
#         "snmpp/Tensor/MultiIndex.hpp" )
# add_library (${TENSOR_OBJ} OBJECT ${TENSOR_SOURCES})
#
#
# ################################################################################
# ## List of headers that will be installed

set (SOURCES
  snmpp/Benchmark/BenchmarkConfig.cpp
  snmpp/Plot/Config.cpp
  snmpp/Plot/Formatter/PrintfFormatter.cpp
  snmpp/Plot/Formatter/StandardFormatter.cpp
  snmpp/Plot/GnuPlotter.cpp
  snmpp/Utils/FormattedOutput.cpp
  snmpp/Utils/Tools.cpp )

set (HEADERS
  snmpp/Benchmark/Benchmark.hpp
  snmpp/Benchmark/BenchmarkConfig.hpp
  snmpp/Math/Core/FuncBase.hpp
  snmpp/Math/Core/Quantity.hpp
  snmpp/Math/Core/Variable.hpp
  snmpp/Math/Core/Variables.hpp
  snmpp/Plot/Config.hpp
  snmpp/Plot/Formatter/FormatterBase.hpp
  snmpp/Plot/Formatter/PrintfFormatter.hpp
  snmpp/Plot/Formatter/StandardFormatter.hpp
  snmpp/Plot/Formatter.hpp
  snmpp/Plot/GnuPlotter.hpp
  snmpp/Plot/PlotterBase.hpp
  snmpp/Tensor/MultiIndex.hpp
  snmpp/Tensor/MultiIter.hpp
  snmpp/Utils/FormattedOutput.hpp
  snmpp/Utils/Sequence.hpp
  snmpp/Utils/Tools.hpp)

set (OBJECT_LIB obj_library)
add_library  (${OBJECT_LIB} OBJECT ${SOURCES} ${HEADERS})

################################################################################
## Creation of the library

FillTargetObjectList("${OBJECT_LIB}" TARGET_OBJECTS_LIST)

if (ENABLE_SHARED )

    add_library (${PROJECT_LIB} SHARED ${TARGET_OBJECTS_LIST} )
    target_include_directories (            ${PROJECT_LIB}
            PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR} )
    set_target_properties (            ${PROJECT_LIB}
            PROPERTIES
            VERSION ${PROJECT_VERSION}
            SOVERSION ${SOVERSION} )
    target_link_libraries (${PROJECT_LIB} Boost::filesystem)
    install (TARGETS ${PROJECT_LIB} LIBRARY DESTINATION ${INSTALL_PATH_LIB} )

endif()

if (ENABLE_STATIC )

    add_library(${PROJECT_STATIC_LIB} STATIC ${TARGET_OBJECTS_LIST} )
    target_link_libraries (${PROJECT_STATIC_LIB} ${Boost_LIBRARIES})
    target_include_directories (            ${PROJECT_STATIC_LIB}
            PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR} )
    install (TARGETS ${PROJECT_STATIC_LIB} DESTINATION ${INSTALL_PATH_LIB} )
endif()

if (NOT ENABLE_STATIC AND NOT ENABLE_SHARED )
    message (FATAL_ERROR "ENABLE_STATIC and ENABLE_SHARED are both off." )
endif()

################################################################################
## Installation of header files

InstallFilesInList ("${HEADERS}" "${INSTALL_PATH_HEADERS}" false)





######################################################################
### CMakeLists.txt ends here
