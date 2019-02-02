cmake_minimum_required (VERSION 3.13)
project (HandsOnOpenCL_tuto LANGUAGES C CXX)
find_package(OpenCL REQUIRED)

macro (add_exec _prefix _item)
  set(_target tuto_${_prefix}_${_item})
  add_executable(${_target} ex${_item}.cpp)
  target_link_libraries(${_target} OpenCL::OpenCL)
endmacro()

add_exec(ex 1)

add_executable(tuto_ex_2 ex2.c)
target_link_libraries(tuto_ex_2 OpenCL::OpenCL)
