macro(add_exec _name _src)
  set(exec_name test-boost-${_name})
  add_executable(${exec_name} ${_src})
  set_target_properties(
   ${exec_name}
   PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
  target_include_directories(${exec_name} PRIVATE ${Boost_INCLUDE_DIRS})
  target_link_libraries(${exec_name} ${Boost_LIBRARIES})
endmacro()

add_exec(asio_task asio/task.cpp)
add_exec(graph_tuto_write graph/examples/graphviz_write.cpp)
add_exec(graph_tuto_read graph/examples/graphviz_read.cpp)
add_exec(concept concept/main.cpp)
add_exec(optional optional/main.cpp)
add_exec(any any/main.cpp)

add_exec(geo-inherit geometry/Inherit.cpp)
add_exec(geo-difference geometry/Difference.cpp)
add_exec(geo-union geometry/Union.cpp)

set(SRC geometry/Point.cpp geometry/Point.hpp)
add_exec(geo-point ${SRC})

add_exec(geo-templated-conversion geometry/TemplatedConversion.cpp)
add_exec(geo-within-strategy geometry/WithinStrategy.cpp)

set(SRC geometry/NumSegment.cpp geometry/Definitions.hpp)
add_exec(geo-num-segment ${SRC})

add_exec(geo-ForEachSegmentTuto geometry/ForEachSegmentTuto.cpp)
add_exec(geo-intersection geometry/Intersection.cpp)
add_exec(geo-overlaps geometry/Overlaps.cpp)
add_exec(geo-AreaClockWisePolygon geometry/AreaClockWisePolygon.cpp)
