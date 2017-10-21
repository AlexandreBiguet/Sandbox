#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 21/10/2017 at 11:34.
#  Copyright © 2017 UAVIA. All rights reserved.
#

add_executable(TestCoreVariables VariablesTests.cpp )

if( ENABLE_SHARED)
    target_link_libraries(TestCoreVariables ${PROJECT_LIB})
else()
    target_link_libraries(TestCoreVariables ${PROJECT_STATIC_LIB})
endif()


# CMakeLists.txt ends here