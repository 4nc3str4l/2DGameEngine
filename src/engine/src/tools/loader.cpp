#include "loader.h"
#include "log.h"
#include <algorithm>
#include "../gfx/stb_image.h"

namespace le
{

// Static Members
std::string Loader::base;
std::map<std::string, Shader*> Loader::shaders;
std::map<std::string, Texture2D*> Loader::textures;

std::vector<GLuint> Loader::vaos;
std::vector<GLuint> Loader::vbos;

void Loader::normalizePath(std::string* path)
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

Shader* Loader::shader(const std::string& path)
{
	std::string fullPath = base + path;
	normalizePath(&fullPath);

    if(Loader::shaders.find(fullPath) != Loader::shaders.end())
    {
        LOG_INFO("Loading Cached Shader ", fullPath);
        return Loader::shaders[path];
    }
    
    LOG_INFO("Trying to load shader ", fullPath);
	auto shader = new Shader(fullPath);
    Loader::shaders.insert({ fullPath, shader });
    return shader;
}

Texture2D* Loader::LoadTexture(const std::string& _texturePath, int* _width, int* _heigth)
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
		Loader::textures.insert({ fullPath, texture });
		return texture;
	}
}

GLuint Loader::CreateVAO()
{
	GLuint vaoID;
    GL_CHECK(glGenVertexArrays(1, &vaoID));
    GL_CHECK(glBindVertexArray(vaoID));
	vaos.push_back(vaoID);
	return vaoID;
}


RawModel* Loader::LoadToVAO(float* positions, int dimensions, int _length)
{
	int vaoID = CreateVAO();
	StoreDataInAttributeList(0, dimensions, positions, _length);
	
	// Unbind
    GL_CHECK(glBindVertexArray(0));
	return new RawModel(vaoID, _length);
}

GLuint Loader::CreateEmptyVBO(int maxNumOfFloats)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	vbos.push_back(VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, maxNumOfFloats * sizeof(float), GL_NONE,  GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return VBO;
}

void Loader::AddInstancedAttributes(int _vao, int _vbo, int _attribute, int _dataSize, int _instancedDataLength, int _offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindVertexArray(_vao);
	glVertexAttribPointer(_attribute, _dataSize, GL_FLOAT, GL_FALSE, _instancedDataLength * 4, (void*)(_offset * 4));
	glVertexAttribDivisor(_attribute, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Loader::UpdateVBO(GLuint _vbo, float* _data, int dataLength)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, dataLength * sizeof(float), GL_NONE, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataLength * 4,  _data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Loader::StoreDataInAttributeList(int _attributeNumber, int _coordinateSize, float* _data, int _length)
{
	GLuint vboID;
    GL_CHECK(glGenBuffers(1, &vboID));
	vbos.push_back(vboID);
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vboID));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _length, &_data[0], GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(_attributeNumber, _coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	glBindVertexArray(0);
}

void Loader::FreeResources()
{
	for (GLuint vao : vaos)
	{
		glDeleteVertexArrays(1, &vao);
	}

	for (GLuint vbo : vbos)
	{
		glDeleteBuffers(1, &vbo);
	}

	for (auto keyVal : textures)
	{
		LOG_FAIL("Free Texture: ", keyVal.first);
	}

	for (auto keyVal : shaders)
	{
		LOG_FAIL("Free Shader: ", keyVal.first);
	}
}

}