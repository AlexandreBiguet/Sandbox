## @Author: Alexandre BIGUET
## @Date:   24 - Jun - 2018

include(CTest)

# Dl the google test framework
enable_testing()

include(${CMAKE_MODULE_PATH}/DownloadProject.cmake)

download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 UPDATE_DISCONNECTED 1)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# add the Cool exec test

add_executable(TestCoolTarget Cool.cpp)
target_link_libraries(TestCoolTarget gtest gmock_main myTest)
add_test(NAME TestCool COMMAND TestCoolTarget)

add_custom_target(check
                  COMMAND GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND} --verbose -C Debug
                  DEPENDS
                  TestCoolTarget)
