#  CMakeLists.txt
#  Created by Alexandre Biguet on 03/09/2018 at 09:58.

add_executable(sort_by_index main.cpp)
set_output_dir_properties(sort_by_index)

add_executable(range_finder RangeFinder.cpp)
target_include_directories(range_finder PRIVATE ${Boost_INCLUDE_DIRS})
set_output_dir_properties(range_finder)