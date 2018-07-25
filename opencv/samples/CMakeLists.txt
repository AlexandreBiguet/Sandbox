macro(add_sample _name _src)
  set(exec_name opencv-samples-${_name})
add_executable(${exec_name} ${_src})
set_target_properties(
        ${exec_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_include_directories(${exec_name} PRIVATE ${OPENCV_INCLUDE_DIRS})
target_link_libraries(${exec_name} ${OPENCV_LDFLAGS} ${OPENCV_LIBRARIES})
endmacro()

add_sample(example-2-1 example-2-1.cpp)
