#include "loader.h"
#include "log.h"
#include <algorithm>
#include "../gfx/stb_image.h"

namespace le
{

// Static Members
std::string Loader::base;
std::map<std::string, std::shared_ptr<Shader>> Loader::shaders;
std::map<std::string, std::shared_ptr<Texture2D>> Loader::textures;

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

std::shared_ptr<Texture2D> Loader::LoadTexture(const std::string& _texturePath, int* _width, int* _heigth)
{
    std::string fullPath = base + _texturePath;
	normalizePath(&fullPath);

    if(Loader::textures.find(fullPath) != Loader::textures.end())
    {
        LOG_INFO("Loading Cached Texture ", fullPath);
        return Loader::textures[fullPath];
    }

    LOG_INFO("Loading Texture ", fullPath);

    // Create Texture object
    Texture2D* texture = new Texture2D();
   
	int nrChannels;
	unsigned char *data = nullptr;

	int w, h;
	if (_texturePath.find(".png") != std::string::npos)
	{
		data = stbi_load(fullPath.c_str(), &w, &h, &nrChannels, STBI_rgb_alpha);
		texture->Internal_Format = GL_RGBA;
		texture->Image_Format = GL_RGBA;
	}
	else
	{
		data = stbi_load(fullPath.c_str(), &w, &h, &nrChannels, STBI_rgb);
	}

	if (!data)
	{
		LOG_FAIL("Failed to load texture: ", fullPath);
		return nullptr;
	}
	else
	{
		// Now generate texture
		texture->Generate(w, h, data);
		stbi_image_free(data);
		std::shared_ptr<Texture2D> t(texture);
		Loader::textures.insert({ fullPath, t });
		return t;
	}
}

}