add_executable(hello-prg main.cpp)
target_link_libraries(hello-prg ${PROJECT_LIB})
install(TARGETS hello-prg DESTINATION ${INSTALL_PATH_BIN} )
