#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 16/10/2017 at 22:24.
#  Copyright © 2017 UAVIA. All rights reserved.
#

add_executable(GetCurrentDateSample GetCurrentDateSample.cpp)

if( ENABLE_SHARED)
    target_link_libraries(GetCurrentDateSample ${PROJECT_LIB})
else()
    target_link_libraries(GetCurrentDateSample ${PROJECT_STATIC_LIB})
endif()

add_executable(FormattedOutputSample FormattedOutputSample.cpp)

if( ENABLE_SHARED)
    target_link_libraries(FormattedOutputSample ${PROJECT_LIB})
else()
    target_link_libraries(FormattedOutputSample ${PROJECT_STATIC_LIB})
endif()



# CMakeLists.txt ends here