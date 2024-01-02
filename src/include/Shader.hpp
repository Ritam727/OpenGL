#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

class ShaderProgramSources
{
public:
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string &filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string &name, glm::vec4 vec);
    void SetUniform2iv(const std::string &name, const int *arr);
    void SetUniform1i(const std::string &name, int value);
    void SetUniformMat4f(const std::string &name, glm::mat4 &ortho);
private:
    int GetUniformLocation(const std::string &name);
    ShaderProgramSources ParseShader(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
};