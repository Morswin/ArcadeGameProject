#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "renderer_utils.hpp"

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
    : m_RendererID(0)
{
    m_RendererID = CreateShader(vertexFilePath, fragmentFilePath);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1fv2(const std::string& name, glm::vec2 value) {
    GLCall(glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(value)));
}

void Shader::SetUniform1fv3(const std::string& name, glm::vec3 value) {
    GLCall(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value)));
}

void Shader::SetUniform1mat4(const std::string& name, glm::mat4 value) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)));
}

void Shader::UpdateUV() {
    glm::vec2 uvScale(1.0f / m_SpriteColumns, 1.0f / m_SpriteRows);
    SetUniform1fv2("u_UVScale", uvScale);
    SetUniform1fv2("u_UVOffset", glm::vec2(uvScale.x * m_SpriteX, uvScale.y * m_SpriteY));
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    GLint success;
    GLchar infoLog[512];
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLCall(glGetShaderInfoLog(id, 512, nullptr, infoLog));
        std::cerr << "Error compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:\n" << infoLog << std::endl;
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    std::string vertexShader;
    {
        std::ifstream fs(vertexShaderPath);
        std::string line;
        std::stringstream ss;
        while ( getline(fs, line) ) {
            ss << line << "\n";
        }
        vertexShader = ss.str();
    }
    std::string fragmentShader;
    {
        std::ifstream fs(fragmentShaderPath);
        std::string line;
        std::stringstream ss;
        while ( getline(fs, line) ) {
            ss << line << "\n";
        }
        fragmentShader = ss.str();
    }
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

int Shader::GetUniformLocation(const std::string name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }

    GLCall(int location = glad_glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    m_UniformLocationCache[name] = location;
    return location;
}

