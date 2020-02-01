#
#

set(_prefix "${PROJECT_NAME}_complete_search")

add_executable(${_prefix}_generating_subsets generating_subsets.cpp)
add_executable(${_prefix}_generating_permutations generating_permutations.cpp)
add_executable(${_prefix}_queens_table queens_table.cpp)

# add_executable(${_prefix}_ )