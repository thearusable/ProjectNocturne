cmake_minimum_required(VERSION 3.13)

set(SDL_VERSION 2.0.0)

find_package(SDL ${SDL_VERSION})

if(NOT ${SDL_FOUND})
   FIND_AND_DOWNLOAD_ZIP_RESOURCE(https://www.libsdl.org/release/SDL2-2.0.9.zip SDL2 2.0.9)
   add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.0.9)
endif()



