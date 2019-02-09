set(sources coin_flipper.cpp coin_flipper.hpp rng.hpp)
add_library(mocking SHARED ${sources})
target_include_directories(mocking
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}
INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${PROJECT_NAME}>)
