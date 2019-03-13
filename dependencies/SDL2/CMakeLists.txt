cmake_minimum_required(VERSION 3.13)

set(SDL_VERSION 2.0.9)

# Function to download resource in zip format
function(FIND_AND_DOWNLOAD_ZIP_RESOURCE ResourceName ResourceURL)
   # download resource if zip file is missing
   if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/SDL2-${SDL_VERSION})
      message(STATUS "${ResourceName} needs to be downloaded!")
      # download
      file(DOWNLOAD ${ResourceURL} ${CMAKE_CURRENT_SOURCE_DIR}/${ResourceName}.zip SHOW_PROGRESS)
      # unzip
	   execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND ${CMAKE_COMMAND} -E tar xvf ${ResourceName}.zip)
   else()
      message(STATUS "${ResourceName} already downloaded")
   endif()
endfunction()

find_package(SDL ${SDL_VERSION})

if(NOT ${SDL_FOUND})
   FIND_AND_DOWNLOAD_ZIP_RESOURCE(SDL2 https://www.libsdl.org/release/SDL2-2.0.9.zip)

   add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL2-${SDL_VERSION})

   #target_include_directories(SDL SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/SDL2-${SDL_VERSION}/include")
endif()



