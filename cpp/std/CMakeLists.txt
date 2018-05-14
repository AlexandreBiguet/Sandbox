###############################################################################

add_executable(std_templatedForLoop templatedForLoop.cpp)
set_target_properties(
        std_templatedForLoop
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )

###############################################################################

add_executable(std_for_each for_each.cpp)
set_target_properties(
        std_for_each
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
