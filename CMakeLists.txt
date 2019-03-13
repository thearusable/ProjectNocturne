cmake_minimum_required(VERSION 3.13)

project(Nocturne)

set(OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH})

add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)
