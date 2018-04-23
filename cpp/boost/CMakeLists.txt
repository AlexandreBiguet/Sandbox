
###############################################################################

add_executable(asio_task asio/task.cpp)
set_target_properties(
        asio_task
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(asio_task ${Boost_LIBRARIES})

###############################################################################

add_executable(graph_tuto_write graph/examples/graphviz_write.cpp)
set_target_properties(
        graph_tuto_write
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(graph_tuto_write ${Boost_LIBRARIES})

###############################################################################

add_executable(graph_tuto_read graph/examples/graphviz_read.cpp)
set_target_properties(
        graph_tuto_read
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(graph_tuto_read ${Boost_LIBRARIES})