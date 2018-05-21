#
#  CMakeLists.txt
#  Sandbox
#
#  Created by Alexandre Biguet on 17/05/2018 at 16:57.
#  Copyright © 2018 . All rights reserved.
#

find_package ( PkgConfig REQUIRED )
pkg_check_modules( geographiclib REQUIRED geographiclib)
include_directories( ${geographiclib_INCLUDE_DIRS})
link_directories( ${geographiclib_LIBRARY_DIRS})

###############################################################################

add_executable(geographiclib_geodesic geodesic.cpp)
set_target_properties(
        geographiclib_geodesic
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(geographiclib_geodesic ${geographiclib_LIBRARIES})

###############################################################################


# CMakeLists.txt ends here
