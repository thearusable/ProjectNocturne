cmake_minimum_required(VERSION 3.13)

set(OPENGL_VERSION 4.5)
set(GLEW_VERSION 2.1.0)

find_package(OpenGL ${OPENGL_VERSION} EXACT REQUIRED)

set_target_properties(OpenGL::GL PROPERTIES IMPORTED_GLOBAL TRUE)

find_package(GLEW ${GLEW_VERSION})

if(GLEW_FOUND)
    set_target_properties(GLEW::GLEW PROPERTIES IMPORTED_GLOBAL TRUE)
else()
   add_library(GLEW INTERFACE IMPORTED GLOBAL)

   if(WIN32)
      FIND_AND_DOWNLOAD_ZIP_RESOURCE(https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip GLEW ${GLEW_VERSION})
      #add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glew-${GLEW_VERSION}/build/cmake)
      target_link_directories(GLEW INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/GLEW-${GLEW_VERSION}/lib/Release/x64")
      target_link_directories(GLEW INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/GLEW-${GLEW_VERSION}/bin/Release/x64")
      target_link_libraries(GLEW INTERFACE "glew32")
   else()
      FIND_AND_DOWNLOAD_ZIP_RESOURCE(https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.tgz GLEW ${GLEW_VERSION})

   endif()

   target_include_directories(GLEW INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/GLEW-${GLEW_VERSION}/include/GL")

endif()