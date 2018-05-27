set( SOURCES
  hello.cpp
)

set (HEADERS
  hello.hpp
)


add_library( ${PROJECT_LIB} SHARED ${SOURCES} ${HEADERS} )

set_target_properties(
        ${PROJECT_LIB}
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${SOVERSION} )

install( TARGETS ${PROJECT_LIB} LIBRARY DESTINATION ${INSTALL_PATH_LIB} )

if (${CMAKE_GENERATOR} STREQUAL Xcode)
  source_group ( TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
  hello.cpp hello.hpp
)
endif()
