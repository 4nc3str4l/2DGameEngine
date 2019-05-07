#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace le { 

class Shader
{
public:
	unsigned int ID;
	
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	Shader(const std::string genericPath);

	void Use();
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetVec2(const std::string &name, const glm::vec2 &value) const;
	void SetVec2(const std::string &name, float x, float y) const;
	void SetVec3(const std::string &name, const glm::vec3 &value) const;
	void SetVec3(const std::string &name, glm::vec3 &value) const;
	void SetVec3(const std::string &name, float x, float y, float z) const;
	void SetVec4(const std::string &name, const glm::vec4 &value) const;
	void SetVec4(const std::string &name, float x, float y, float z, float w);
	void SetMat2(const std::string &name, const glm::mat2 &mat) const;
	void SetMat3(const std::string &name, const glm::mat3 &mat) const;
	void SetMat4(const std::string &name, const glm::mat4 &mat) const;

	void SetBool(GLuint _location, bool value) const;
	void SetInt(GLuint _location, int value) const;
	void SetFloat(GLuint _location, float value) const;
	void SetVec2(GLuint _location, const glm::vec2 &value) const;
	void SetVec2(GLuint _location, float x, float y) const;
	void SetVec3(GLuint _location, const glm::vec3 &value) const;
	void SetVec3(GLuint _location, glm::vec3 &value) const;
	void SetVec3(GLuint _location, float x, float y, float z) const;
	void SetVec4(GLuint _location, const glm::vec4 &value) const;
	void SetVec4(GLuint _location, float x, float y, float z, float w);
	void SetMat2(GLuint _location, const glm::mat2 &mat) const;
	void SetMat3(GLuint _location, const glm::mat3 &mat) const;
	void SetMat4(GLuint _location, const glm::mat4 &mat) const;

	void BindAttribute(const std::string &_name, const int _attribute) const;

private:
	void Create(const char* vertexPath, const char* fragmentPath, const char* geometryPath /*= nullptr*/);
	void CheckCompileErrors(GLuint shader, std::string type);
};
}