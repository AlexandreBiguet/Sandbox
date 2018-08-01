## Author: Alexandre BIGUET

set(SOURCES utils.cpp)
set(HEADERS utils.hpp)
add_library(${LIB_UTILS_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${LIB_UTILS_NAME} docopt)
target_include_directories(${LIB_UTILS_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

