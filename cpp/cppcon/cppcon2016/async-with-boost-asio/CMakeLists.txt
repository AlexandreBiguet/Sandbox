
add_executable(cppcon2016_boost_asio_simple_timer simple_timer.cpp)
set_target_properties(
  cppcon2016_boost_asio_simple_timer
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(cppcon2016_boost_asio_simple_timer ${Boost_LIBRARIES})

#

add_executable(cppcon2016_boost_asio_timer_with_thread timer_with_thread.cpp)
set_target_properties(
  cppcon2016_boost_asio_timer_with_thread
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(cppcon2016_boost_asio_timer_with_thread ${Boost_LIBRARIES})

#

add_executable(cppcon2016_boost_asio_posting_work posting_work.cpp)
set_target_properties(
  cppcon2016_boost_asio_posting_work
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(cppcon2016_boost_asio_posting_work ${Boost_LIBRARIES})

#

add_executable(cppcon2016_boost_asio_strand strand.cpp)
set_target_properties(
  cppcon2016_boost_asio_strand
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(cppcon2016_boost_asio_strand ${Boost_LIBRARIES})

add_subdirectory(ChatServer)
