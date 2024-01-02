#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.hpp"

int Shader::GetUniformLocation(const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Error! Uniform " << name << " doesn't exist!" << std::endl;
    else
        m_UniformLocationCache[name] = location;
    return location;
}

Shader::Shader(const std::string &filepath)
    : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSources src = ParseShader(filepath);
    m_RendererID = CreateShader(src.VertexSource, src.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string &name, glm::vec4 vec)
{
    GLCall(int location = GetUniformLocation(name));
    if (location != -1)
        GLCall(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));
}

void Shader::SetUniform2iv(const std::string &name, const int *arr)
{
    GLCall(int location = GetUniformLocation(name));
    if (location != -1)
        GLCall(glUniform1iv(location, 2, arr));
}

void Shader::SetUniform1i(const std::string &name, int value)
{
    GLCall(int location = GetUniformLocation(name));
    if (location != -1)
        GLCall(glUniform1i(location, value));
}

void Shader::SetUniformMat4f(const std::string &name, glm::mat4 &ortho)
{
    GLCall(int location = GetUniformLocation(name));
    if (location != -1)
        GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &ortho[0][0]));
}

ShaderProgramSources Shader::ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);
    enum ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    ShaderType type = ShaderType::NONE;
    std::stringstream ss[2];

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    int size_ = source.size();
    GLCall(glShaderSource(id, 1, &src, &size_));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, 1024, &length, message));
        std::cout << "FAILED TO COMPILE " << ((type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAG") << " SHADER!" << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));

        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
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
