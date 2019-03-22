cmake_minimum_required(VERSION 3.14)

option(TEST_HUNTER_USE_HUNTER_PACKAGE_MANAGER "Whether to use Hunter package manager" ON)
option(TEST_HUNTER_SET_LOCAL_ROOT "Use build directory as the Hunter Root" OFF)

if(TEST_HUNTER_USE_HUNTER_PACKAGE_MANAGER)
    if(TEST_HUNTER_SET_LOCAL_ROOT)
        set(HUNTER_ROOT ${CMAKE_BINARY_DIR})
    endif()

    execute_process(COMMAND wget https://raw.githubusercontent.com/hunter-packages/gate/master/cmake/HunterGate.cmake)
    include(${CMAKE_BINARY_DIR}/HunterGate.cmake)
    HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.142.tar.gz"
        SHA1 "1d841ca74150c92054896a7f6d88a123dd9e615d"
        LOCAL)
endif()

project(test_hunter_package_manager LANGUAGES CXX VERSION 0.0.1)

if(TEST_HUNTER_USE_HUNTER_PACKAGE_MANAGER)
    hunter_add_package(Boost)
endif()

find_package(Boost 1.65.1 EXACT REQUIRED)

add_executable(hunter_test_exec main.cpp)
target_link_libraries(hunter_test_exec PRIVATE Boost::boost)


include(GNUInstallDirs)
install(TARGETS hunter_test_exec DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})
