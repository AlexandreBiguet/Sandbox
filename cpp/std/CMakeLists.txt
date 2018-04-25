###############################################################################

add_executable(std_templatedForLoop templatedForLoop.cpp)
set_target_properties(
        std_templatedForLoop
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
# target_link_libraries(std_templatedForLoop)
