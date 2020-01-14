cmake_minimum_required(VERSION 3.14)
project(interview_prep LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME}_1 main1.cpp)
add_executable(${PROJECT_NAME}_shape shape.cpp)
add_executable(${PROJECT_NAME}_third_latest_data third_latest_data.cpp)
add_executable(${PROJECT_NAME}_tree_of_errors tree_of_errors.cpp)

# add_executable(${PROJECT_NAME}_ )