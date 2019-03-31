cmake_minimum_required(VERSION 3.13)

set(MODULE_NAME Nocturne)
project(${MODULE_NAME})

set(OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH})

add_library(${MODULE_NAME} INTERFACE)

target_sources(${MODULE_NAME} INTERFACE ${SOURCES} INTERFACE ${HEADERS})
target_include_directories(${MODULE_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries (${MODULE_NAME} INTERFACE SDL2)
target_compile_features(${MODULE_NAME} INTERFACE cxx_std_17)

add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)
