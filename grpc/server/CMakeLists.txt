set(client_binary "server")
add_executable(${client_binary} main.cpp)
target_link_libraries(${client_binary} api gRPC::grpc++_reflection protobuf::libprotobuf)
