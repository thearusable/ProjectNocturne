cmake_minimum_required(VERSION 3.13)

set(GLM_VERSION 0.9.9.5)

find_package(glm ${GLM_VERSION})

if(NOT ${glm_FOUND})
   FIND_AND_DOWNLOAD_ZIP_RESOURCE(https://github.com/g-truc/glm/archive/0.9.9.5.zip GLM ${GLM_VERSION})
   #add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm-${GLM_VERSION})

   add_library(GLM INTERFACE IMPORTED GLOBAL)
   target_include_directories(GLM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/glm-${GLM_VERSION}/glm")
endif()
