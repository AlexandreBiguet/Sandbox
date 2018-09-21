cmake_minimum_required (VERSION 3.7.2)

project(Codingame LANGUAGES C CXX VERSION 0.0.1)

option(BUILD_WITH_CCACHE "Build with CCache" ON)

if(BUILD_WITH_CCACHE)

    if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
        SET(ENV{PATH} /usr/local/opt/ccache/libexec:$ENV{PATH})
    elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        SET(ENV{PATH} /usr/lib/ccache:$ENV{PATH})
    else()
        message(FATAL_ERROR "CCache is not handled for your system: ${CMAKE_SYSTEM_NAME}")
    endif()

    find_program(CCACHE_FOUND ccache)

    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif(CCACHE_FOUND)

endif()

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

macro(add_exec _name _src)
  set(exec_name cdg_${_name})
  add_executable(${exec_name} ${_src})
  set_target_properties(
    ${exec_name}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
endmacro()

add_exec(power_of_thor_ep1 power_of_thor_ep1.cpp)
add_exec(shadows_of_the_night_ep1 shadows_of_the_night_ep1.cpp)

add_subdirectory(inge)
