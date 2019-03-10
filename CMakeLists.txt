cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Nocturne)

set(CMAKE_DEBUG_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug/)
set(CMAKE_RELEASE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/)
set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies)

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
   FIND_AND_DOWNLOAD_RESOURCE(ZIP https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip GLEW)

   SET(OPENGL_INCLUDE_DIR "${RESOURCES_PATH}/glew-2.1.0/include/GL")
   SET(OPENGL_opengl_LIBRARY glew32 glew32s opengl32)
   link_directories("${RESOURCES_PATH}/glew-2.1.0/lib/Release/x64")
endif()

if(NOT ${SDL_FOUND})
   FIND_AND_DOWNLOAD_RESOURCE(ZIP https://www.libsdl.org/release/SDL2-2.0.9.zip SDL_SOURCE)

   add_subdirectory(${RESOURCES_PATH}/SDL2-2.0.9)
   SET(SDL_INCLUDE_DIR "${RESOURCES_PATH}/SDL2-2.0.9/include")
   SET(SDL_LIBRARY SDL2)
   link_directories("${CMAKE_CURRENT_BINARY_DIR}/Dependencies/SDL2-2.0.9/Debug/" "${CMAKE_BINARY_DIR}/Dependencies/SDL2-2.0.9/Release/")
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

# Copy dll files
if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
   add_custom_command(TARGET Nocturne POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different  
           "${CMAKE_CURRENT_BINARY_DIR}/Dependencies/SDL2-2.0.9/Debug/SDL2d.dll" $<TARGET_FILE_DIR:Nocturne>)  
else()
   add_custom_command(TARGET Nocturne POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different  
           "${CMAKE_CURRENT_BINARY_DIR}/Dependencies/SDL2-2.0.9/Release/SDL2.dll" $<TARGET_FILE_DIR:Nocturne>)  
endif()