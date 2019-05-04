#pragma once

#include <string>
#include "../gfx/shader.h"
#include <map>
#include "../gfx/texture_2d.h"

namespace le
{
class Loader
{
public:
    static std::string base;
    static std::map<std::string, std::shared_ptr<Shader>> shaders;
    static std::map<std::string, std::shared_ptr<Texture2D>> textures;
public:
    static void init(char** argv);
    static std::shared_ptr<Shader> shader(const std::string& path);
    static std::shared_ptr<Texture2D> LoadTexture(const std::string& _texturePath, int* _width = nullptr, int* _heigth = nullptr);
};
}