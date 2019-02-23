cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
cmake_policy(VERSION 3.7)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

project(Nocturne)

OPTION(USE_D2D_WSI "Build the project using Direct to Display swapchain" OFF)
OPTION(USE_WAYLAND_WSI "Build the project using Wayland swapchain" OFF)

set(RESOURCE_INSTALL_DIR "" CACHE PATH "Path to install resources to (leave empty for running uninstalled)")

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
	  execute_process(WORKING_DIRECTORY ${RESOURCES_PATH} COMMAND cmake -E tar xvf ${RESOURCES_PATH}/${ResourceName}/${ResourceName}.zip)
   else()
      message(STATUS "${ResourceName} found!")
   endif()
endfunction()


FIND_AND_DOWNLOAD_RESOURCE(GLM https://github.com/g-truc/glm/releases/download/0.9.9.3/glm-0.9.9.3.zip)
FIND_AND_DOWNLOAD_GIT_RESOURCE(VULCAN_H https://github.com/KhronosGroup/Vulkan-Headers.git)
FIND_AND_DOWNLOAD_GIT_RESOURCE(VULCAN_HPP https://github.com/KhronosGroup/Vulkan-Hpp.git)


set(RESOURCERS_INCLUDES ${RESOURCES_PATH}/GLM
						${RESOURCES_PATH}/VULCAN_H/include
						${RESOURCES_PATH}/VULCAN_HPP)




# Use FindVulkan module added with CMAKE 3.7
if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
	message(STATUS "Using module to find Vulkan")
	find_package(Vulkan)
endif()

IF(WIN32)
	IF (NOT Vulkan_FOUND)
		find_library(Vulkan_LIBRARY NAMES vulkan-1 vulkan PATHS ${CMAKE_SOURCE_DIR}/libs/vulkan)
		IF (Vulkan_LIBRARY)
			set(Vulkan_FOUND ON)
			MESSAGE("Using bundled Vulkan library version")
		ENDIF()
	ENDIF()
	#find_library(ASSIMP_LIBRARIES NAMES assimp libassimp.dll.a PATHS ${CMAKE_SOURCE_DIR}/libs/assimp)
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_WIN32_KHR")
ELSE(WIN32)
	IF (NOT Vulkan_FOUND)
		find_library(Vulkan_LIBRARY NAMES vulkan HINTS "$ENV{VULKAN_SDK}/lib" "${CMAKE_SOURCE_DIR}/libs/vulkan" REQUIRED)
		IF (Vulkan_LIBRARY)
			set(Vulkan_FOUND ON)
			MESSAGE("Using bundled Vulkan library version")
		ENDIF()
	ENDIF()
	find_package(ASSIMP REQUIRED)
	find_package(Threads REQUIRED)
IF(USE_D2D_WSI)
	MESSAGE("Using direct to display extension...")
	add_definitions(-D_DIRECT2DISPLAY)
ELSEIF(USE_WAYLAND_WSI)
	find_program(PKG_CONFIG pkg-config)
	if (NOT PKG_CONFIG)
		message(FATAL_ERROR "pkg-config binary not found")
	endif ()
	find_package(Wayland REQUIRED)
	if (NOT WAYLAND_FOUND)
		message(FATAL_ERROR "Wayland development package not found")
	endif ()
	pkg_check_modules(WAYLAND_PROTOCOLS REQUIRED wayland-protocols)
	if (NOT WAYLAND_PROTOCOLS_FOUND)
		message(FATAL_ERROR "Wayland protocols package not found")
	endif ()
	find_program(WAYLAND_SCANNER wayland-scanner)
	if (NOT WAYLAND_SCANNER)
		message(FATAL_ERROR "wayland-scanner binary not found")
	endif ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_WAYLAND_KHR")
	include_directories(${WAYLAND_INCLUDE_DIR})
	execute_process(COMMAND ${PKG_CONFIG} --variable=pkgdatadir wayland-protocols OUTPUT_VARIABLE protocol_dir OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND ${WAYLAND_SCANNER} client-header ${protocol_dir}/stable/xdg-shell/xdg-shell.xml xdg-shell-client-protocol.h
			COMMAND ${WAYLAND_SCANNER} private-code ${protocol_dir}/stable/xdg-shell/xdg-shell.xml xdg-shell-protocol.c)
	include_directories(${CMAKE_BINARY_DIR})
ELSE(USE_D2D_WSI)
	find_package(XCB REQUIRED)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_XCB_KHR")
ENDIF(USE_D2D_WSI)
	# Todo : android?
ENDIF(WIN32)

IF (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
	message(STATUS ${Vulkan_LIBRARY})
ENDIF()

# Set preprocessor defines
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX -D_USE_MATH_DEFINES")

# Clang specific stuff
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-switch-enum")
endif()


add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-std=c++11)

file(GLOB HEADERS *.hpp)
file(GLOB SOURCES *.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${RESOURCERS_INCLUDES})

set(SOURCE_FOLDER_NAME src)

# Function for building single example
#file(GLOB SOURCES *.cpp ${BASE_HEADERS} ${SOURCE_FOLDER_NAME}/*.cpp)
#SET(MAIN_CPP ${SOURCE_FOLDER_NAME}/${SOURCE_FOLDER_NAME}.cpp)
#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER_NAME}/main.cpp)
SET(MAIN_CPP ${SOURCE_FOLDER_NAME}/main.cpp)
#ENDIF()
# imgui example requires additional source files
#IF(${SOURCE_FOLDER_NAME} STREQUAL "imgui")
#	file(GLOB ADD_SOURCE external/imgui/*.cpp)
#	SET(SOURCES ${SOURCES} ${ADD_SOURCE})
#ENDIF()
# Add shaders
#set(SHADER_DIR data/shaders/${SOURCE_FOLDER_NAME})
#file(GLOB SHADERS "${SHADER_DIR}/*.vert" "${SHADER_DIR}/*.frag" "${SHADER_DIR}/*.geom" "${SHADER_DIR}/*.tesc" "${SHADER_DIR}/*.tese")
#source_group("Shaders" FILES ${SHADERS})
if(WIN32)
	add_executable(${SOURCE_FOLDER_NAME} WIN32 ${MAIN_CPP} ${HEADERS} ${SOURCES} ${SHADERS})
	target_link_libraries(${SOURCE_FOLDER_NAME} base ${Vulkan_LIBRARY} ${ASSIMP_LIBRARIES} ${WINLIBS})
else(WIN32)
	add_executable(${SOURCE_FOLDER_NAME} ${MAIN_CPP} ${HEADERS} ${SOURCES} ${SHADERS})
	target_link_libraries(${SOURCE_FOLDER_NAME} base )
endif(WIN32)

if(RESOURCE_INSTALL_DIR)
	install(TARGETS ${SOURCE_FOLDER_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

#if(RESOURCE_INSTALL_DIR)
#	add_definitions(-DVK_EXAMPLE_DATA_DIR=\"${RESOURCE_INSTALL_DIR}/\")
#	install(DIRECTORY data/ DESTINATION ${RESOURCE_INSTALL_DIR}/)
#else()
#	add_definitions(-DVK_EXAMPLE_DATA_DIR=\"${CMAKE_SOURCE_DIR}/data/\")
#endif()

# Compiler specific stuff
IF(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
ENDIF(MSVC)

IF(WIN32)
	# Nothing here (yet)
ELSE(WIN32)
	link_libraries(${XCB_LIBRARIES} ${Vulkan_LIBRARY} ${Vulkan_LIBRARY} ${ASSIMP_LIBRARIES} ${WAYLAND_CLIENT_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
ENDIF(WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")