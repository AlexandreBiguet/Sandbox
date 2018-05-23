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

###############################################################################

add_executable(std_inheritance inheritance.cpp)
set_target_properties(
        std_inheritance
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )

###############################################################################

add_executable(std_inheritance2 inheritance2.cpp)
set_target_properties(
        std_inheritance2
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )

###############################################################################

add_executable(std_conversion conversion.cpp)
set_target_properties(
        std_conversion
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )


###############################################################################
