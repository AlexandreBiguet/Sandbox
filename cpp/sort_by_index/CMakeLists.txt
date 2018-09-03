#  CMakeLists.txt
#  Created by Alexandre Biguet on 03/09/2018 at 09:58.

add_executable(sort_by_index main.cpp)
set_target_properties(sort_by_index PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
