#pragma once

#include <string>
#include "../gfx/shader.h"
#include <map>

namespace le
{
class Loader
{
public:
    static std::string base;
    static std::map<std::string, std::shared_ptr<Shader>> shaders;
public:
    static void init(char** argv);
    static std::shared_ptr<Shader> shader(const std::string& path);
};
}