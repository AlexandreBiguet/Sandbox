
# -----------------------------------------------------------------------------
# --- macro for boost test

macro(add_test _target _src)
  add_executable(${_target} ${_src})
  target_link_libraries(${_target} PRIVATE Boost::coroutine Boost::log)

  if(${Boost_VERSION} VERSION_LESS_EQUAL "106800")
    # TODO Check if boost::coroutine2 still available after 1.69
    target_compile_definitions(${_target}
                               PRIVATE
                               -DBOOST_COROUTINES_NO_DEPRECATION_WARNING
                               -DBOOST_LOG_DYN_LINK)
  endif()

  install(TARGETS ${_target} DESTINATION ${CMAKE_INSTALL_BINDIR}/flex_test)
endmacro()

# -----------------------------------------------------------------------------
# --- adding boost tests

add_test(test_http_client_coro test_http_client_coro.cpp)

add_test(test_http_client_asio test_http_client_asio.cpp)

add_test(test_circular_container test_circular_container.cpp)

# -----------------------------------------------------------------------------
# --- adding http client tests

add_test(test_http_client_session test_http_client_session.cpp)
target_include_directories(test_http_client_session PRIVATE ${nlohmanjson_SOURCE_DIR})

# -----------------------------------------------------------------------------
# --- adding algorithms tests

add_test(test_cycle_detect test_cycle_detect.cpp)

# -----------------------------------------------------------------------------
# --- adding json test

add_test(test_json_parse_from_string test_json_parse_from_string.cpp)
target_include_directories(test_json_parse_from_string PRIVATE ${nlohmanjson_SOURCE_DIR})

# -----------------------------------------------------------------------------
# ---
