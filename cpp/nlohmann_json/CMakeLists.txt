
add_executable(nlohmann_json main.cpp)
set_target_properties(
        nlohmann_json
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_include_directories(nlohmann_json PRIVATE ${NLOHMANN_JSON_PROJECT_SOURCE_DIR})        
# target_link_libraries(nlohmann_json ${geographiclib_LIBRARIES})
