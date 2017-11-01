#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 02/11/2017 at 00:17.
#  Copyright © 2017 UAVIA. All rights reserved.
#

add_executable(SampleMultiIndexIntegral MultiIndex/main.cpp)

if( ENABLE_SHARED)
    target_link_libraries(SampleMultiIndexIntegral ${PROJECT_LIB})
else()
    target_link_libraries(SampleMultiIndexIntegral ${PROJECT_STATIC_LIB})
endif()


# CMakeLists.txt ends here