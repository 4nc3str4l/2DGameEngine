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

add_executable(LostEngine2D 
    ${CMAKE_SOURCE_DIR}/engine/tools/log.h
    ${CMAKE_SOURCE_DIR}/engine/tools/log.cpp
    
    ${CMAKE_SOURCE_DIR}/engine/gfx/shader.h
    ${CMAKE_SOURCE_DIR}/engine/gfx/shader.cpp    
    
    ${CMAKE_SOURCE_DIR}/engine/gfx/window.h 
    ${CMAKE_SOURCE_DIR}/engine/gfx/window.cpp
    
    ${CMAKE_SOURCE_DIR}/engine/gfx/sprite_renderer.h 
    ${CMAKE_SOURCE_DIR}/engine/gfx/sprite_renderer.cpp

    ${CMAKE_SOURCE_DIR}/engine/gfx/texture_2d.h 
    ${CMAKE_SOURCE_DIR}/engine/gfx/texture_2d.cpp

    ${CMAKE_SOURCE_DIR}/engine/gfx/stb_image.h
    ${CMAKE_SOURCE_DIR}/engine/gfx/stb_image.cpp 

    ${CMAKE_SOURCE_DIR}/engine/gfx/sprite.h
    ${CMAKE_SOURCE_DIR}/engine/gfx/sprite.cpp 
    
    ${CMAKE_SOURCE_DIR}/engine/gfx/raw_model.h
    ${CMAKE_SOURCE_DIR}/engine/gfx/raw_model.cpp 

    ${CMAKE_SOURCE_DIR}/engine/gfx/text_renderer.h
    ${CMAKE_SOURCE_DIR}/engine/gfx/text_renderer.cpp 

    ${CMAKE_SOURCE_DIR}/engine/tools/loader.h
    ${CMAKE_SOURCE_DIR}/engine/tools/loader.cpp

    ${CMAKE_SOURCE_DIR}/engine/tools/input.h
    ${CMAKE_SOURCE_DIR}/engine/tools/input.cpp

    ${CMAKE_SOURCE_DIR}/engine/tools/maths.h
    ${CMAKE_SOURCE_DIR}/engine/tools/maths.cpp

    ${CMAKE_SOURCE_DIR}/engine/main.cpp
    ${CMAKE_SOURCE_DIR}/dependencies/glad/src/glad.c 
)

target_link_libraries(LostEngine2D glfw freetype)