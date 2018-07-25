macro(add_exec _name _src)
  set(exec_name cppcon2016_${_name})
  add_executable(${exec_name} ${_src})
  set_target_properties(
   ${exec_name}
   PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
  target_include_directories(${exec_name} PRIVATE ${Boost_INCLUDE_DIRS})
  target_link_libraries(${exec_name} ${Boost_LIBRARIES})
endmacro()

add_exec(boost_asio_simple_timer simple_timer.cpp)
add_exec(boost_asio_timer_with_thread timer_with_thread.cpp)
add_exec(boost_asio_posting_work posting_work.cpp)
add_exec(boost_asio_strand strand.cpp)

set(SRC ChatServer/main.cpp ChatServer/generic_server.hpp
        ChatServer/chat_handler.hpp)
add_exec(boost_asio_chat_server ${SRC})
