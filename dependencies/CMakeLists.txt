cmake_minimum_required(VERSION 3.13)

# Function to download resource in zip format
function(FIND_AND_DOWNLOAD_ZIP_RESOURCE ResourceURL ResourceName Version)
   # download resource if zip file is missing
   if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${ResourceName}-${Version})
      message(STATUS "${ResourceName} needs to be downloaded!")

      # download
      file(DOWNLOAD ${ResourceURL} ${CMAKE_CURRENT_SOURCE_DIR}/${ResourceName}.zip SHOW_PROGRESS STATUS STAT LOG LG)

      # print status and log if file wasn't downloaded properly

      message("File status = ${STAT}")
      message("File LOG = ${LG}")


      # unzip
	   execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND ${CMAKE_COMMAND} -E tar xvf ${ResourceName}.zip)
   else()
      message(STATUS "${ResourceName} already downloaded")
   endif()
endfunction()

add_subdirectory(SDL2)
add_subdirectory(OpenGL)

