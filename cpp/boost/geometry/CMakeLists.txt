
###############################################################################

add_executable(BoostGeometryInherit Inherit.cpp)
set_target_properties(
        BoostGeometryInherit
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryInherit ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryDifference Difference.cpp)
set_target_properties(
        BoostGeometryDifference
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryDifference ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryUnion Union.cpp)
set_target_properties(
        BoostGeometryUnion
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryUnion ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryPoint Point.cpp Point.hpp)
set_target_properties(
        BoostGeometryPoint
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryPoint ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryTemplatedConversion TemplatedConversion.cpp)
set_target_properties(
        BoostGeometryTemplatedConversion
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryTemplatedConversion ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryWithinStrategy WithinStrategy.cpp)
set_target_properties(
        BoostGeometryWithinStrategy
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryWithinStrategy ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryNumSegment NumSegment.cpp Definitions.hpp)
set_target_properties(
        BoostGeometryNumSegment
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryNumSegment ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryForEachSegmentTuto ForEachSegmentTuto.cpp)
set_target_properties(
        BoostGeometryForEachSegmentTuto
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryForEachSegmentTuto ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryIntersection Intersection.cpp)
set_target_properties(
        BoostGeometryIntersection
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryIntersection ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryOverlaps Overlaps.cpp)
set_target_properties(
        BoostGeometryOverlaps
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryOverlaps ${Boost_LIBRARIES})

###############################################################################

add_executable(BoostGeometryAreaClockWisePolygon AreaClockWisePolygon.cpp)
set_target_properties(
        BoostGeometryAreaClockWisePolygon
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(BoostGeometryAreaClockWisePolygon ${Boost_LIBRARIES})

###############################################################################
# CMakeLists.txt ends here
