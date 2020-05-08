find_package(spdlog REQUIRED)

set(binary "server")
add_executable(${binary} main.cpp)
target_link_libraries(${binary} api gRPC::grpc++_reflection protobuf::libprotobuf spdlog::spdlog)
target_include_directories(${binary} PRIVATE ${CMAKE_BINARY_DIR})