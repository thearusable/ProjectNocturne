cmake_minimum_required(VERSION 3.13)

find_package(SDL2 QUIET)

if(NOT ${SDL2_FOUND})
   set(VERSION 2.0.9)
   FIND_AND_DOWNLOAD_ZIP_RESOURCE(https://www.libsdl.org/release/SDL2-${VERSION}.zip SDL2 ${VERSION})
   add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2-${VERSION})
else()
   add_library(SDL2 INTERFACE IMPORTED GLOBAL)
   target_link_directories(SDL2 INTERFACE ${SDL2_LIBDIR})
   target_include_directories(SDL2 INTERFACE ${SDL2_INCLUDE_DIRS})
   target_link_libraries(SDL2 INTERFACE ${SDL2_LIBRARIES})
endif()



