cmake_minimum_required(VERSION 3.13)

set(MODULE_NAME Input)

project(${MODULE_NAME})

file(GLOB HEADERS "*.hpp")
file(GLOB SOURCES "*.cpp")

add_library(${MODULE_NAME} OBJECT)

target_sources(${MODULE_NAME} PRIVATE ${SOURCES} PUBLIC ${HEADERS})
target_include_directories(${MODULE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries (${MODULE_NAME} PUBLIC SDL2)
target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)