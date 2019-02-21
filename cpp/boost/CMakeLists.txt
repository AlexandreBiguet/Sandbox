macro(add_exec _name _src)
  set(exec_name boost_${_name})
  add_executable(${exec_name} ${_src})
  set_target_properties(
   ${exec_name}
   PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
  target_include_directories(${exec_name} PRIVATE ${Boost_INCLUDE_DIRS})
  target_link_libraries(${exec_name} ${Boost_LIBRARIES})
endmacro()

if (${Boost_VERSION} LESS 106501)
  add_exec(asio_task asio/task.cpp)
endif()

if (${Boost_VERSION} GREATER 106600)
  add_exec(asio_timer1 asio/timer1.cpp)
  add_exec(asio_timer2 asio/timer2.cpp)
  add_exec(asio_timer3 asio/timer3.cpp)
  add_exec(asio_timer4 asio/timer4.cpp)
  add_exec(asio_task2 asio/task2.cpp)
endif()

add_exec(graph_tuto_write graph/examples/graphviz_write.cpp)
add_exec(graph_tuto_read graph/examples/graphviz_read.cpp)
add_exec(concept concept/main.cpp)
add_exec(optional optional/main.cpp)
add_exec(any any/main.cpp)

add_exec(geo_inherit geometry/Inherit.cpp)
add_exec(geo_difference geometry/Difference.cpp)
add_exec(geo_union geometry/Union.cpp)

set(SRC geometry/Point.cpp geometry/Point.hpp)
add_exec(geo_point ${SRC})

add_exec(geo_templated_conversion geometry/TemplatedConversion.cpp)
add_exec(geo_within_strategy geometry/WithinStrategy.cpp)

set(SRC geometry/NumSegment.cpp geometry/Definitions.hpp)
add_exec(geo_num_segment ${SRC})

add_exec(geo_for_each_segment_tuto geometry/ForEachSegmentTuto.cpp)
add_exec(geo_intersection geometry/Intersection.cpp)
add_exec(geo_overlaps geometry/Overlaps.cpp)
add_exec(geo_area_clock_wise_polygon geometry/AreaClockWisePolygon.cpp)

add_exec(functional_hash functional/hash.cpp)
add_exec(state_machine_simple_tuto state_machine/player_simple_tuto.cpp)
add_exec(state_machine_turnstile state_machine/turnstile.cpp)
add_exec(state_machine_turnstile_functor_frontend state_machine/turnstile_functor_frontend.cpp)
