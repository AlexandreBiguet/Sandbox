add_executable(type_concept main.cpp)
target_include_directories(type_concept PRIVATE ${Boost_INCLUDE_DIRS})
set_output_dir_properties(type_concept)
