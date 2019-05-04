#include "loader.h"
#include "log.h"
#include <algorithm>

namespace le
{

// Static Members
std::string Loader::base;
std::map<std::string, std::shared_ptr<Shader>> Loader::shaders;

void normalizePath(std::string* path)
{
    #if defined(_WIN64)
    std::replace(path->begin(), path->end(),  '/', '\\');
    #else
    std::replace(path->begin(), path->end(), '\\', '/');
    #endif
}

void Loader::init(char** argv)
{
    std::string aux(argv[0]);
    #if defined(_WIN64)
        int pos = (int)aux.rfind('\\');
    #else
        int pos = aux.rfind('/');
    #endif
    Loader::base = aux.substr(0, pos+1);
    LOG_INFO(Loader::base);
}

std::shared_ptr<Shader> Loader::shader(const std::string& path)
{
	std::string fullPath = base + path;
	normalizePath(&fullPath);

    if(Loader::shaders.find(fullPath) != Loader::shaders.end())
    {
        LOG_INFO("Loading Cached Shader ", fullPath);
        return Loader::shaders[path];
    }
    
    LOG_INFO("Trying to load shader ", fullPath);
    auto shader = std::make_shared<Shader>(fullPath);
    Loader::shaders.insert({ fullPath, shader});
    return shader;
}

}