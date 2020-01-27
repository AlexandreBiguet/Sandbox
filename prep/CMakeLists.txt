cmake_minimum_required(VERSION 3.14)
project(interview_prep LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME}_1 main1.cpp)
add_executable(${PROJECT_NAME}_shape shape.cpp)
add_executable(${PROJECT_NAME}_third_latest_data third_latest_data.cpp)
add_executable(${PROJECT_NAME}_tree_of_errors tree_of_errors.cpp)
add_executable(${PROJECT_NAME}_find_range find_range.cpp find_range.hpp)
add_executable(${PROJECT_NAME}_climbing_leaderboard climbing_leaderboard.cpp)

add_executable(${PROJECT_NAME}_gcd_euclid gcd_euclid.cpp)
add_executable(${PROJECT_NAME}_find_missing_element_in_sorted_array find_missing_element_in_sorted_array.cpp)

# add_executable(${PROJECT_NAME}_ )

add_subdirectory(complete_search)
add_subdirectory(tall_ranges)

