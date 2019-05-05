cmake_minimum_required (VERSION 3.9.0)
project(LostEngine2D)

# GLFW For window handling
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw-3.3)

# FreeType for Text Rendering
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/freetype-2.10.0)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/freetype-2.10.0/include)

# Math Library
include_directories(${CMAKE_SOURCE_DIR}/dependencies/glm)

# Glad for OpenGL functions
include_directories(${CMAKE_SOURCE_DIR}/dependencies/glad/include)

# Include the own include folder to have shorter paths
include_directories(${CMAKE_SOURCE_DIR}/engine/include/tools)
include_directories(${CMAKE_SOURCE_DIR}/engine/include/gfx)

add_executable(LostEngine2D 
    ${CMAKE_SOURCE_DIR}/engine/src/gfx/shader.cpp    
    ${CMAKE_SOURCE_DIR}/engine/src/gfx/window.cpp
    ${CMAKE_SOURCE_DIR}/engine/src/gfx/sprite_renderer.cpp
    ${CMAKE_SOURCE_DIR}/engine/src/gfx/texture_2d.cpp
    ${CMAKE_SOURCE_DIR}/engine/src/gfx/stb_image.cpp 
    ${CMAKE_SOURCE_DIR}/engine/src/gfx/sprite.cpp 
    ${CMAKE_SOURCE_DIR}/engine/src/gfx/raw_model.cpp 
    ${CMAKE_SOURCE_DIR}/engine/src/gfx/text_renderer.cpp 
    ${CMAKE_SOURCE_DIR}/engine/src/tools/log.cpp
    ${CMAKE_SOURCE_DIR}/engine/src/tools/loader.cpp
    ${CMAKE_SOURCE_DIR}/engine/src/tools/input.cpp
    ${CMAKE_SOURCE_DIR}/engine/src/tools/maths.cpp


    ${CMAKE_SOURCE_DIR}/engine/main.cpp
    ${CMAKE_SOURCE_DIR}/dependencies/glad/src/glad.c 
)

target_link_libraries(LostEngine2D glfw freetype)