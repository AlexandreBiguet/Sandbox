
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

###############################################################################

<<<<<<< HEAD
add_executable(geo_inherit geometry/inherit.cpp)
set_target_properties(
        geo_inherit
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(geo_inherit ${Boost_LIBRARIES})

###############################################################################
=======
add_executable(concept_test concept/main.cpp)
set_target_properties(
        concept_test
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(concept_test ${Boost_LIBRARIES})

###############################################################################

add_executable(optional_test optional/main.cpp)
set_target_properties(
        optional_test
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(optional_test ${Boost_LIBRARIES})
>>>>>>> 5050c9305efa6ee73aace1d1c0a9c7f8b3ef7ebf
