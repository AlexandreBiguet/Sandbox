#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 22/10/2017 at 17:12.
#  Copyright © 2017 UAVIA. All rights reserved.
#

add_executable(SampleBenchmark main.cpp)

if( ENABLE_SHARED)
    target_link_libraries(SampleBenchmark ${PROJECT_LIB})
else()
    target_link_libraries(SampleBenchmark ${PROJECT_STATIC_LIB})
endif()


# CMakeLists.txt ends here