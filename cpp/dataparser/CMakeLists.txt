
add_executable(dataparser main.cpp DataParser.cpp DataParser.hpp)
target_include_directories(dataparser PRIVATE ${Boost_INCLUDE_DIRS})
set_output_dir_properties(dataparser)

macro(copy_data _file)
  if(EXISTS ${_file})
    file(COPY ${_file} DESTINATION ${CMAKE_BINARY_DIR}/bin/)
  else()
    message(STATUS "No file ${_file} found")
  endif()
endmacro()

copy_data(${CMAKE_CURRENT_SOURCE_DIR}/space_sep.txt)
copy_data(${CMAKE_CURRENT_SOURCE_DIR}/semicol_sep.txt)
copy_data(${CMAKE_CURRENT_SOURCE_DIR}/gen.py)