cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(Nocturne)

set(CMAKE_DEBUG_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug/)
set(CMAKE_RELEASE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/)
set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies)

# Dependencies
# Function to download resource from git repo
function(FIND_AND_DOWNLOAD_GIT_RESOURCE ResourceName ResourceURL)
   if(NOT EXISTS ${RESOURCES_PATH}/${ResourceName})
      message(STATUS "${ResourceName} need to be downloaded!")
      execute_process(WORKING_DIRECTORY ${RESOURCES_PATH} COMMAND git clone ${ResourceURL} ${RESOURCES_PATH}/${ResourceName})
   else()
      message(STATUS "${ResourceName} found!")
   endif()
endfunction()

# Function to download resource in zip format
function(FIND_AND_DOWNLOAD_RESOURCE ResourceName ResourceURL)
   # download resource if zip file is missing
   if(NOT EXISTS ${RESOURCES_PATH}/${ResourceName}/${ResourceName}.zip)
      message(STATUS "${ResourceName} need to be downloaded!")
	  # download
      file(DOWNLOAD ${ResourceURL} ${RESOURCES_PATH}/${ResourceName}/${ResourceName}.zip SHOW_PROGRESS)
	  # unzip
	  execute_process(WORKING_DIRECTORY ${RESOURCES_PATH} COMMAND ${CMAKE_COMMAND} -E tar xvf ${RESOURCES_PATH}/${ResourceName}/${ResourceName}.zip)
   else()
      message(STATUS "${ResourceName} found!")
   endif()
endfunction()

# Function to copy dll files to build directory
function(COPY_LIBS_TO_BUILD_DIR BuildDirectory)
   find_path(OUTPUT_EXISTS ${BuildDirectory} ${CMAKE_BINARY_DIR})
   if(NOT ${OUTPUT_EXISTS})
      execute_process(COMMAND mkdir -p ${BuildDirectory})
      execute_process(COMMAND cp ${RESOURCES_PATH}/glew-2.1.0/bin/Release/x64/glew32.dll ${BuildDirectory})
      execute_process(COMMAND cp ${RESOURCES_PATH}/SDL2.dll ${BuildDirectory})
   endif()
endfunction()

FIND_AND_DOWNLOAD_RESOURCE(GLEW https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip)
FIND_AND_DOWNLOAD_RESOURCE(SDL_SOURCE https://www.libsdl.org/release/SDL2-2.0.9.zip)
FIND_AND_DOWNLOAD_RESOURCE(SDL_LIB https://www.libsdl.org/release/SDL2-2.0.9-win32-x64.zip)

set(RESOURCERS_INCLUDES ${RESOURCES_PATH}/glew-2.1.0/include/GL
						${RESOURCES_PATH}/SDL2-2.0.9//include)

set(RESOURCES_LIBS ${RESOURCES_PATH}/glew-2.1.0/lib/Release/x64
				   ${RESOURCES_PATH}/glew-2.1.0/lib/Release/x64)

COPY_LIBS_TO_BUILD_DIR(${CMAKE_DEBUG_RUNTIME_OUTPUT_DIRECTORY})
COPY_LIBS_TO_BUILD_DIR(${CMAKE_RELEASE_RUNTIME_OUTPUT_DIRECTORY})

file(GLOB HEADERS "src/*.hpp")
file(GLOB SOURCES "src/*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${RESOURCERS_INCLUDES})
link_directories(${RESOURCES_LIBS})

if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    else()
        # nothing special for gcc at the moment
    endif()
endif()

add_executable(Nocturne  ${HEADERS} ${SOURCES})
target_link_libraries (Nocturne glew32 glew32s opengl32)