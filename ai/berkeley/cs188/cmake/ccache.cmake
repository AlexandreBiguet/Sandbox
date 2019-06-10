
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
  set(ENV{PATH} /usr/local/opt/ccache/libexec:$ENV{PATH})
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(ENV{PATH} /usr/lib/ccache:$ENV{PATH})
else()
  message(FATAL_ERROR
          "CCache is not handled for your system: ${CMAKE_SYSTEM_NAME}")
endif()

find_program(CCACHE_FOUND ccache)

if(CCACHE_FOUND)
  message(STATUS "Building with ccache : ccache found")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)
