cmake_minimum_required (VERSION 3.9.0)
project(LostEngine2D)

# GLFW For window handling
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/glfw-3.3)

# FreeType for Text Rendering
add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies/freetype-2.10.0)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/freetype-2.10.0/include)

# Math Library
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glm)

# Glad for OpenGL functions
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glad/include)

# Include the own include folder to have shorter paths
include_directories(${PROJECT_SOURCE_DIR}/engine/include/tools)
include_directories(${PROJECT_SOURCE_DIR}/engine/include/gfx)
include_directories(${PROJECT_SOURCE_DIR}/engine/include/logic)

# Get the current source dir and add it as a local variable
SET_PROPERTY(GLOBAL PROPERTY MyGlobalProperty ${PROJECT_SOURCE_DIR})

function(lost_engine_includes)
    # Recover the local variable in the function call to add the includes in other projects
    GET_PROPERTY(Source_dir GLOBAL PROPERTY MyGlobalProperty)
    include_directories(${Source_dir}/dependencies/glm)
    include_directories(${Source_dir}/dependencies/glad/include)
    include_directories(${Source_dir}/dependencies/glfw-3.3/include)
    include_directories(${Source_dir}/dependencies/freetype-2.10.0/include)
    include_directories(${Source_dir}/engine/include)
endfunction(lost_engine_includes) 

add_library(LostEngine2D STATIC
    ${PROJECT_SOURCE_DIR}/engine/src/gfx/shader.cpp    
    ${PROJECT_SOURCE_DIR}/engine/src/gfx/window.cpp
    ${PROJECT_SOURCE_DIR}/engine/src/gfx/sprite_renderer.cpp
    ${PROJECT_SOURCE_DIR}/engine/src/gfx/texture_2d.cpp
    ${PROJECT_SOURCE_DIR}/engine/src/gfx/stb_image.cpp 
    ${PROJECT_SOURCE_DIR}/engine/src/gfx/sprite.cpp 
    ${PROJECT_SOURCE_DIR}/engine/src/gfx/raw_model.cpp 
    ${PROJECT_SOURCE_DIR}/engine/src/gfx/text_renderer.cpp
     
    ${PROJECT_SOURCE_DIR}/engine/src/tools/log.cpp
    ${PROJECT_SOURCE_DIR}/engine/src/tools/loader.cpp
    ${PROJECT_SOURCE_DIR}/engine/src/tools/input.cpp
    ${PROJECT_SOURCE_DIR}/engine/src/tools/maths.cpp

    ${PROJECT_SOURCE_DIR}/engine/src/logic/lost_engine.cpp
    ${PROJECT_SOURCE_DIR}/dependencies/glad/src/glad.c 
)

target_link_libraries(LostEngine2D glfw freetype)