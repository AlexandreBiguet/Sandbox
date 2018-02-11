#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 16/10/2017 at 22:24.
#

add_executable(SampleGetCurrentDate GetCurrentDateSample.cpp)

if( ENABLE_SHARED)
    target_link_libraries(SampleGetCurrentDate ${PROJECT_LIB})
else()
    target_link_libraries(SampleGetCurrentDate ${PROJECT_STATIC_LIB})
endif()

add_executable(SampleFormattedOutput FormattedOutputSample.cpp)

if( ENABLE_SHARED)
    target_link_libraries(SampleFormattedOutput ${PROJECT_LIB})
else()
    target_link_libraries(SampleFormattedOutput ${PROJECT_STATIC_LIB})
endif()



# CMakeLists.txt ends here
