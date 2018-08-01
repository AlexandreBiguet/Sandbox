## Author: Alexandre BIGUET

add_exec(NAME doc-video-writer SOURCES video_writer.cpp)
add_exec(NAME doc-similarity-measurement
         SOURCES similarity_measurement.cpp
         LIBRARIES ${LIB_UTILS_NAME}
         INCLUDES ${CMAKE_SOURCE_DIR})
