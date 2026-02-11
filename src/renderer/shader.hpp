#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource {
    std::string vertexSourceProgram;
    std::string fragmentSourceProgram;
};

class Shader {
private:
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    int m_SpriteX{0};
    int m_SpriteY{0};
    int m_SpriteColumns{1};
    int m_SpriteRows{1};
public:
    Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1fv2(const std::string& name, glm::vec2 value);
    void SetUniform1fv3(const std::string& name, glm::vec3 value);
    void SetUniform1mat4(const std::string& name, glm::mat4 value);
    void UpdateUV();

    inline void SetSpriteSize(int columns, int rows) { m_SpriteColumns = columns; m_SpriteRows = rows; }
    inline void SetSpriteCoordinate(int x, int y) { m_SpriteX = x; m_SpriteY = y; }
private:
    unsigned int CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    bool CompileShader();
    unsigned int CompileShader(unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string name);
};

#endif // SHADER_H
