#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 23/10/2017 at 20:52.
#

add_executable(BenchmarkFormattedOutput main.cpp ../BenchmarkConfig.hpp)

if (ENABLE_SHARED)
    target_link_libraries(BenchmarkFormattedOutput ${PROJECT_LIB})
else()
    target_link_libraries(BenchmarkFormattedOutput ${PROJECT_STATIC_LIB})
endif()

# CMakeLists.txt ends here
