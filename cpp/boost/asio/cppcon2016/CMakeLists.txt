
add_executable(boost_asio_cppcon2016_simple_timer simple_timer.cpp)
set_target_properties(
        boost_asio_cppcon2016_simple_timer
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(boost_asio_cppcon2016_simple_timer ${Boost_LIBRARIES})

#

add_executable(boost_asio_cppcon2016_timer_with_thread timer_with_thread.cpp)
set_target_properties(
        boost_asio_cppcon2016_timer_with_thread
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(boost_asio_cppcon2016_timer_with_thread ${Boost_LIBRARIES})

#

add_executable(boost_asio_cppcon2016_posting_work posting_work.cpp)
set_target_properties(
        boost_asio_cppcon2016_posting_work
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(boost_asio_cppcon2016_posting_work ${Boost_LIBRARIES})

#

add_executable(boost_asio_cppcon2016_strand strand.cpp)
set_target_properties(
        boost_asio_cppcon2016_strand
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(boost_asio_cppcon2016_strand ${Boost_LIBRARIES})

add_subdirectory(ChatServer)
