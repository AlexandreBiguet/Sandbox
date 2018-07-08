add_executable(boost_asio_cppcon2016_chat_server main.cpp generic_server.hpp chat_handler.hpp)
set_target_properties(
        boost_asio_cppcon2016_chat_server
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_link_libraries(boost_asio_cppcon2016_chat_server ${Boost_LIBRARIES})
