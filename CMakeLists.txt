cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Nocturne)

set(CMAKE_DEBUG_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug/)
set(CMAKE_RELEASE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/)
set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies)
set(OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/app/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${OUTPUT_PATH})

# Dependencies
function(FIND_AND_DOWNLOAD_RESOURCE Type ResourceURL Resource)
   if(${Type} STREQUAL "ZIP")
      FIND_AND_DOWNLOAD_ZIP_RESOURCE(${Resource} ${ResourceURL})
   elseif(${Type} STREQUAL "GIT")
      FIND_AND_DOWNLOAD_GIT_RESOURCE(${Resource} ${ResourceURL})
   else()
      message(FATAL_ERROR "Unsuported dependency type=${Type}")
   endif()
endfunction()

# Function to download resource from git repo
function(FIND_AND_DOWNLOAD_GIT_RESOURCE ResourceName ResourceURL)
   if(NOT EXISTS ${RESOURCES_PATH}/${ResourceName})
      message(STATUS "${ResourceName} needs to be downloaded!")
      execute_process(WORKING_DIRECTORY ${RESOURCES_PATH} COMMAND git clone ${ResourceURL} ${RESOURCES_PATH}/${ResourceName})
   else()
      message(STATUS "${ResourceName} found!")
   endif()
endfunction()

# Function to download resource in zip format
function(FIND_AND_DOWNLOAD_ZIP_RESOURCE ResourceName ResourceURL)
   # download resource if zip file is missing
   if(NOT EXISTS ${RESOURCES_PATH}/${ResourceName}/${ResourceName}.zip)
      message(STATUS "${ResourceName} needs to be downloaded!")
      # download
      file(DOWNLOAD ${ResourceURL} ${RESOURCES_PATH}/${ResourceName}/${ResourceName}.zip SHOW_PROGRESS)
      # unzip
	   execute_process(WORKING_DIRECTORY ${RESOURCES_PATH} COMMAND ${CMAKE_COMMAND} -E tar xvf ${RESOURCES_PATH}/${ResourceName}/${ResourceName}.zip)
   else()
      message(STATUS "${ResourceName} found!")
   endif()
endfunction()

include(FindOpenGL)
include(FindSDL)

if(NOT ${OPENGL_FOUND})
   message(FATAL_ERROR "OpenGL not found!")
endif()

if(NOT ${SDL_FOUND})
   FIND_AND_DOWNLOAD_RESOURCE(ZIP https://www.libsdl.org/release/SDL2-2.0.9.zip SDL_SOURCE)

   add_subdirectory(${RESOURCES_PATH}/SDL2-2.0.9)
   SET(SDL_INCLUDE_DIR "${RESOURCES_PATH}/SDL2-2.0.9/include")
   SET(SDL_LIBRARY SDL2)
   link_directories("${RESOURCES_PATH}/SDL2-2.0.9/Debug/" "${RESOURCES_PATH}/SDL2-2.0.9/Release/")
endif()

set(RESOURCERS_INCLUDES ${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

file(GLOB HEADERS "src/*.hpp")
file(GLOB SOURCES "src/*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${RESOURCERS_INCLUDES})

if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-Wall" "-Wextra" "$<$<CONFIG:RELEASE>:-O3>")
endif()

add_executable(Nocturne ${HEADERS} ${SOURCES})
target_link_libraries (Nocturne ${SDL_LIBRARY} ${OPENGL_opengl_LIBRARY})