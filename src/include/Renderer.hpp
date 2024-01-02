#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <signal.h>

#include "IndexBuffer.hpp"
#include "Shader.hpp"

class VertexArray;

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x)   GLClearError();\
                    x;\
                    ASSERT(GLLogCall(__FILE__, #x, __LINE__))

void GLClearError();
bool GLLogCall(const char *file, const char *function, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer &ib, const Shader &shader);
};