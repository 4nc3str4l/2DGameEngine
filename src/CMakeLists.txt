cmake_minimum_required (VERSION 3.9.0)
project(FistStreaming)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/glad/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw-3.3)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/glm)

add_executable(FirstStreaming 
    ${CMAKE_SOURCE_DIR}/engine/tools/log.h
    ${CMAKE_SOURCE_DIR}/engine/tools/log.cpp
    
    ${CMAKE_SOURCE_DIR}/engine/gfx/shader.h
    ${CMAKE_SOURCE_DIR}/engine/gfx/shader.cpp    
    
    ${CMAKE_SOURCE_DIR}/engine/gfx/window.h 
    ${CMAKE_SOURCE_DIR}/engine/gfx/window.cpp
    
    ${CMAKE_SOURCE_DIR}/engine/main.cpp
    ${CMAKE_SOURCE_DIR}/dependencies/glad/src/glad.c 
)

target_link_libraries(FirstStreaming glfw)