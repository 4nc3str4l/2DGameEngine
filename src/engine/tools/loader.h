#pragma once

#include <string>
#include <map>
#include "../gfx/shader.h"
#include "../gfx/texture_2d.h"
#include "../gfx/raw_model.h"
#include <vector>

inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
        abort();
    }
}

#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            glGetError(); \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif

namespace le
{
class Loader
{
public:
    static std::string base;
    static std::map<std::string, std::shared_ptr<Shader>> shaders;
    static std::map<std::string, std::shared_ptr<Texture2D>> textures;

    static std::vector<GLuint> vaos;
	static std::vector<GLuint> vbos;
public:
    static void init(char** argv);
    static std::shared_ptr<Shader> shader(const std::string& path);
    static std::shared_ptr<Texture2D> LoadTexture(const std::string& _texturePath, int* _width = nullptr, int* _heigth = nullptr);

    static GLuint CreateVAO();
    static GLuint CreateEmptyVBO(int maxNumOfFloats);
    static RawModel* LoadToVAO(float* positions, int dimensions, int _arraySize);
    static void AddInstancedAttributes(int _vao, int _vbo, int _attribute, int _dataSize, int _instancedDataLength, int _offset);
    static void UpdateVBO(GLuint _vbo, float* _data , int dataLength);
    static void StoreDataInAttributeList(int _attributeNumber, int _coordinateSize, float* _data, int _length);

	static void FreeResources();
};
}