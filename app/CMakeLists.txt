set(MODULE_NAME Editor)

project(${MODULE_NAME})

add_executable(${MODULE_NAME} "main.cpp")
target_link_libraries (${MODULE_NAME} PRIVATE Window)
target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)