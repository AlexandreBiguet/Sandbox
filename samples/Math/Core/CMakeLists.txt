#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 16/10/2017 at 22:25.
#  Copyright © 2017 UAVIA. All rights reserved.
#


add_executable(CoreQuantitySample QuantitySample.cpp)

if( ENABLE_SHARED)
    target_link_libraries(CoreQuantitySample ${PROJECT_LIB})
else()
    target_link_libraries(CoreQuantitySample ${PROJECT_STATIC_LIB})
endif()

add_executable(CoreVariableSample VariableSample.cpp )

if( ENABLE_SHARED)
    target_link_libraries(CoreVariableSample ${PROJECT_LIB})
else()
    target_link_libraries(CoreVariableSample ${PROJECT_STATIC_LIB})
endif()


# CMakeLists.txt ends here