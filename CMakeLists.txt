## Author: Alexandre BIGUET
## Created: 2018/04/23 9:28

cmake_minimum_required (VERSION 3.5.1)

project(Sandbox LANGUAGES C CXX VERSION 0.0.1)

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

find_package(
        Boost 1.64
        COMPONENTS
        thread
        coroutine
        REQUIRED)

set ( RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

###############################################################################

add_executable(cpp_boost_asio_task cpp/boost/asio/task.cpp)
set_target_properties(
        cpp_boost_asio_task
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/cpp/boost/asio )
target_link_libraries(cpp_boost_asio_task ${Boost_LIBRARIES})

###############################################################################

