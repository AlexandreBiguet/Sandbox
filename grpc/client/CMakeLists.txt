set(client_binary "client")
add_executable(${client_binary} main.cpp)
target_link_libraries(${client_binary} api gRPC::grpc++_reflection protobuf::libprotobuf)
target_include_directories(${client_binary} PRIVATE ${CMAKE_BINARY_DIR})