
###############################################################################
# Plugins library

include( GNUInstallDirs )

add_library( SandboxPlugins SHARED plugs.cpp ${VERSION_SOURCE} )

set_target_properties(
        SandboxPlugins
        PROPERTIES
        VERSION 1.2.3
        SOVERSION 1 )
target_include_directories(SandboxPlugins PRIVATE ${Boost_INCLUDE_DIRS}) 
install( TARGETS SandboxPlugins LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR} )

###############################################################################

add_executable(dll_plugin main.cpp)
set_target_properties(
        dll_plugin
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )
target_include_directories(dll_plugin PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(dll_plugin ${Boost_LIBRARIES})


# executable loader
