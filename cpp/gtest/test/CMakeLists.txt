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

add_subdirectory(
  ${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)


macro(test_decl _prefix _src)
  add_executable(${_prefix}_test_target ${_src})
  target_link_libraries(${_prefix}_test_target PRIVATE gtest gmock myTest mocking)
  add_test(NAME ${_prefix}_test COMMAND ${_prefix}_test_target)
endmacro()

test_decl(cool Cool.cpp)
test_decl(stuff Stuff.cpp)
test_decl(coin_flipper coin_flipper.cpp)

add_custom_target(check
                  COMMAND GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND} --verbose -C Debug
                  DEPENDS
                  cool_test_target stuff_test_target)

if(MYTEST_CODE_COVERAGE)
  set(COVERAGE_EXCLUDES '${CMAKE_BINARY_DIR}/*')

  setup_target_for_coverage(
    NAME coverage
    EXECUTABLE ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target check #TestCoolTarget # TestStuffTarget
    DEPENDENCIES myTest
  )
endif()
