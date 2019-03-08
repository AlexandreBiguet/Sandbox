macro(add_sample _target _file _libs)
  add_executable(${_target} ${_file})
  target_link_libraries(${_target} PRIVATE "${_libs}")
  install(TARGETS ${_target} DESTINATION ${CMAKE_INSTALL_BINDIR}/flex_sample)
endmacro()

add_sample(sample_http_get http_get.cpp flex)
add_sample(sample_http_put http_put.cpp flex)
add_sample(sample_http_post http_post.cpp flex)
