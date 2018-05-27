set( SOURCES
        project/Demo/Demo.cpp
        project/Demo/Demo2.cpp
        project/Test/Test.cpp
)

set (HEADERS
  project/Demo/Demo.hpp
  project/Test/Test.hpp
)


add_library( ${PROJECT_LIB} SHARED ${SOURCES} ${HEADERS} )

set_target_properties(
        ${PROJECT_LIB}
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${SOVERSION} )

install( TARGETS ${PROJECT_LIB} LIBRARY DESTINATION ${INSTALL_PATH_LIB} )

if (${CMAKE_GENERATOR} STREQUAL Xcode)
  # source_group ( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES project/Demo/Demo.cpp project/Demo/Demo2.cpp project/Demo/Demo.hpp)
  # source_group ( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES project/Test/Test.cpp project/Test/Test.hpp)
  source_group ( TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
  project/Test/Test.cpp
  project/Test/Test.hpp
  project/Demo/Demo.cpp
  project/Demo/Demo2.cpp
  project/Demo/Demo.hpp
)
endif()
