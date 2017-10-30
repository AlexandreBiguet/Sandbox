#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 21/10/2017 at 11:33.
#  Copyright © 2017 UAVIA. All rights reserved.
#

############

add_executable(TestCoreVariables Core/VariablesTests.cpp )

if( ENABLE_SHARED)
    target_link_libraries(TestCoreVariables ${PROJECT_LIB})
else()
    target_link_libraries(TestCoreVariables ${PROJECT_STATIC_LIB})
endif()

############

add_executable( TestPlot Plot/main.cpp )

if( ENABLE_SHARED)
    target_link_libraries(TestPlot ${PROJECT_LIB})
else()
    target_link_libraries(TestPlot ${PROJECT_STATIC_LIB})
endif()



# CMakeLists.txt ends here