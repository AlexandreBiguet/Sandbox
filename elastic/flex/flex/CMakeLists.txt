# -----------------------------------------------------------------------------
# ---

set(LIBRARY_NAME flex)

# -----------------------------------------------------------------------------
# ---

file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE PUBLIC_HEADERS *.hpp)

# -----------------------------------------------------------------------------
# ---

add_library(${LIBRARY_NAME} SHARED ${SOURCES} ${PUBLIC_HEADERS})

# -----------------------------------------------------------------------------
# ---

target_link_libraries(
  ${LIBRARY_NAME}
  PUBLIC
  Boost::boost
  Boost::coroutine
  Boost::system
  PRIVATE
  Boost::log)

# -----------------------------------------------------------------------------
# ---

target_include_directories(
  ${LIBRARY_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/>
  $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/>
  ${nlohmanjson_SOURCE_DIR})

# -----------------------------------------------------------------------------
# ---

if(${Boost_VERSION} VERSION_LESS_EQUAL "106800")
  # TODO Check if boost::coroutine2 still available after 1.69
  target_compile_definitions(
    ${LIBRARY_NAME}
    PUBLIC
    -DBOOST_COROUTINES_NO_DEPRECATION_WARNING
    -DBOOST_LOG_DYN_LINK)
endif()

# -----------------------------------------------------------------------------
# ---

install(
  TARGETS ${LIBRARY_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})

# -----------------------------------------------------------------------------
# ---

macro(install_headers src dst)
  foreach(file ${src})
    get_filename_component(file ${file} ABSOLUTE)
    get_filename_component(file_dir ${file} DIRECTORY)
    string(REPLACE "${PROJECT_SOURCE_DIR}" "" file_dir "${file_dir}")
    file(TO_CMAKE_PATH "${dst}/${file_dir}" dst_dir)
    install(FILES ${file} DESTINATION ${dst_dir} COMPONENT Devel)
  endforeach()
endmacro()

install_headers(${PUBLIC_HEADERS} ${CMAKE_INSTALL_INCLUDEDIR})

install_headers(
  ${nlohmanjson_SOURCE_DIR}/nlohmann/json.hpp ${CMAKE_INSTALL_INCLUDEDIR}) # yurk
