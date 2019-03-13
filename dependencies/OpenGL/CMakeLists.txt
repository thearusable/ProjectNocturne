cmake_minimum_required(VERSION 3.13)

set(OPENGL_VERSION 4.5)

find_package(OpenGL ${OPENGL_VERSION} EXACT REQUIRED)

if(opengl_FOUND)
    set_target_properties(OpenGL::opengl
                         PROPERTIES IMPORTED_GLOBAL TRUE)
endif()