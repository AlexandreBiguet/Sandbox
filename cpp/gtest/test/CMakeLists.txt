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

# add the Stuff exec test

add_executable(TestStuffTarget Stuff.cpp)
target_link_libraries(TestStuffTarget gtest gmock_main myTest)
add_test(NAME TestStuff COMMAND TestStuffTarget)

add_custom_target(check
                  COMMAND GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND} --verbose -C Debug
                  DEPENDS
                  TestCoolTarget TestStuffTarget)

if(${MYTEST_CODE_COVERAGE})
  set(COVERAGE_EXCLUDES '${CMAKE_BINARY_DIR}/*')

  setup_target_for_coverage(
    NAME coverage
    EXECUTABLE ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target check #TestCoolTarget # TestStuffTarget
    DEPENDENCIES myTest
  )
endif()
