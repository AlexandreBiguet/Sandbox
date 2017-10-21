#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 16/10/2017 at 22:25.
#  Copyright © 2017 UAVIA. All rights reserved.
#


add_executable(SampleCoreQuantity QuantitySample.cpp)

if( ENABLE_SHARED)
    target_link_libraries(SampleCoreQuantity ${PROJECT_LIB})
else()
    target_link_libraries(SampleCoreQuantity ${PROJECT_STATIC_LIB})
endif()


add_executable(SampleCoreVariable VariableSample.cpp )

if( ENABLE_SHARED)
    target_link_libraries(SampleCoreVariable ${PROJECT_LIB})
else()
    target_link_libraries(SampleCoreVariable ${PROJECT_STATIC_LIB})
endif()


add_executable(SampleCoreVariables VariablesSample.cpp )

if( ENABLE_SHARED)
    target_link_libraries(SampleCoreVariables ${PROJECT_LIB})
else()
    target_link_libraries(SampleCoreVariables ${PROJECT_STATIC_LIB})
endif()


add_executable(SampleCoreFunc FuncSample.cpp )

if( ENABLE_SHARED)
    target_link_libraries(SampleCoreFunc ${PROJECT_LIB})
else()
    target_link_libraries(SampleCoreFunc ${PROJECT_STATIC_LIB})
endif()

# CMakeLists.txt ends here