cmake_minimum_required (VERSION 3.9.0)
project(FistStreaming)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/glad/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw-3.3)

add_executable(FirstStreaming 
	main.cpp
	${CMAKE_SOURCE_DIR}/dependencies/glad/src/glad.c 
)

target_link_libraries(FirstStreaming glfw)