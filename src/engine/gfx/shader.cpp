#include "shader.h"
#include "../tools/log.h"

namespace le {

Shader::Shader(const std::string genericPath)
{
    std::string fs = genericPath + ".fs";
    std::string vs = genericPath + ".vs";
    this->Create(vs.c_str(), fs.c_str(), nullptr);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath /*= nullptr*/)
{
    this->Create(vertexPath, fragmentPath, geometryPath);
}

void Shader::Create(const char* vertexPath, const char* fragmentPath, const char* geometryPath /*= nullptr*/)
{
    LOG_INFO("Building Shader: ", vertexPath);
    
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
        if (geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure e)
    {
        LOG_FAIL("FILE NOT SUCCESFULLY READ");
    }
    
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex, fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    
    unsigned int geometry;
    if (geometryPath != nullptr)
    {
        const char * gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        CheckCompileErrors(geometry, "GEOMETRY");
    }
    
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    
    if (geometryPath != nullptr)
        glAttachShader(ID, geometry);

    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");

    // As the shaders are already linked it will be no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr)
        glDeleteShader(geometry);    
}

void Shader::Use() 
{
    glUseProgram(ID);
}

void Shader::SetBool(const std::string &name, bool value) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform1i(location, (int)value);
}

void Shader::SetInt(const std::string &name, int value) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform1i(location, value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform1f(location, value);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform2fv(location, 1, &value[0]);
}

void Shader::SetVec2(const std::string &name, float x, float y) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform2f(location, x, y);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform3fv(location, 1, &value[0]);
}

void Shader::SetVec3(const std::string &name, glm::vec3 &value) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform3fv(location, 1, &value[0]);
}

void Shader::SetVec3(const std::string &name, float x, float y, float z) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform3f(location, x, y, z);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform4fv(location, 1, &value[0]);
}

void Shader::SetVec4(const std::string &name, float x, float y, float z, float w)
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniform4f(location, x, y, z, w);
}

void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetBool(GLuint _location, bool value) const
{
    glUniform1i(_location, (int)value);
}

void Shader::SetInt(GLuint _location, int value) const
{
    glUniform1i(_location, value);
}

void Shader::SetFloat(GLuint _location, float value) const
{
    glUniform1f(_location, value);
}

void Shader::SetVec2(GLuint _location, const glm::vec2 & value) const
{
    glUniform2fv(_location, 1, &value[0]);
}

void Shader::SetVec2(GLuint _location, float x, float y) const
{
    glUniform2f(_location, x, y);
}

void Shader::SetVec3(GLuint _location, const glm::vec3 & value) const
{
    glUniform3fv(_location, 1, &value[0]);
}

void Shader::SetVec3(GLuint _location, float x, float y, float z) const
{
    glUniform3f(_location, x, y, z);
}

void Shader::SetVec4(GLuint _location, const glm::vec4 & value) const
{
    glUniform4fv(_location, 1, &value[0]);
}

void Shader::SetVec4(GLuint _location, float x, float y, float z, float w)
{
    glUniform4f(_location, x, y, z, w);
}

void Shader::SetMat2(GLuint _location, const glm::mat2 & mat) const
{
    glUniformMatrix2fv(_location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(GLuint _location, const glm::mat3 & mat) const
{
    glUniformMatrix3fv(_location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(GLuint _location, const glm::mat4 & mat) const
{
    glUniformMatrix4fv(_location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::BindAttribute(const std::string &_name, const int _attribute) const
{
    glBindAttribLocation(ID, _attribute, _name.c_str());
}

void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
}