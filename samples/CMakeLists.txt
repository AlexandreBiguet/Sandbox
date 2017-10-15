#
#  CMakeLists.txt
#  snmpp
#
#  Created by Alexandre Biguet on 13/10/2017 at 23:44.
#  Copyright © 2017 UAVIA. All rights reserved.
#


add_executable(fakeSample fake/main.cpp)
target_include_directories(
        fakeSample
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src/snmpp/fake)

if( ENABLE_SHARED)
    target_link_libraries(fakeSample ${PROJECT_LIB})
else()
    target_link_libraries(fakeSample ${PROJECT_STATIC_LIB})
endif()
# CMakeLists.txt ends here