#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 02/11/2017 at 00:17.
#  Copyright © 2017 UAVIA. All rights reserved.
#

add_executable(SampleMultiIndexCompleteInt MultiIndex/ComleteInt.cpp)

if( ENABLE_SHARED)
    target_link_libraries(SampleMultiIndexCompleteInt ${PROJECT_LIB})
else()
    target_link_libraries(SampleMultiIndexCompleteInt ${PROJECT_STATIC_LIB})
endif()

add_executable(SampleMultiIndexPartialInt MultiIndex/PartialInt.cpp)

if( ENABLE_SHARED)
    target_link_libraries(SampleMultiIndexPartialInt ${PROJECT_LIB})
else()
    target_link_libraries(SampleMultiIndexPartialInt ${PROJECT_STATIC_LIB})
endif()


# CMakeLists.txt ends here