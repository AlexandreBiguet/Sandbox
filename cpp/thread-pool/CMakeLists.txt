## Author: Alexandre BIGUET
## Created : Thu Nov 22 17:08:24 CET 2018

include(FetchContent)

FetchContent_Declare(
  vitvit_ctpl
  GIT_REPOSITORY git@github.com:vit-vit/CTPL.git
  GIT_TAG        ctpl_v.0.0.2
)

FetchContent_GetProperties(vitvit_ctpl)

if(NOT vitvit_ctpl_POPULATED)
  FetchContent_Populate(vitvit_ctpl)
  # add_subdirectory(${vitvit_ctpl_SOURCE_DIR}
  #                  ${vitvit_ctpl_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(thread_pool main.cpp)

set_target_properties(
 thread_pool
 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )

target_include_directories(
  thread_pool
  PRIVATE ${Boost_INCLUDE_DIRS} ${vitvit_ctpl_SOURCE_DIR})
