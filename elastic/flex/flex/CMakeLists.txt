set(LIBRARY_NAME flex)

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE PUBLIC_HEADERS *.hpp)

add_library(${LIBRARY_NAME} SHARED ${SOURCES} ${PUBLIC_HEADERS})

install(TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})

macro(install_headers src dst)
  foreach(file ${src})
    get_filename_component(file ${file} ABSOLUTE)
    get_filename_component(file_dir ${file} DIRECTORY)
    string(REPLACE "${PROJECT_SOURCE_DIR}/lib/" "" file_dir "${file_dir}")
    file(TO_CMAKE_PATH "${dst}/${file_dir}" dst_dir)
    install(FILES ${file} DESTINATION ${dst_dir} COMPONENT Devel)
  endforeach()
endmacro()

install_headers(${PUBLIC_HEADERS} ${CMAKE_INSTALL_INCLUDEDIR})
