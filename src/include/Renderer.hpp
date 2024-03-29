#pragma once

#include "glad/glad.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <signal.h>

#include "IndexBuffer.hpp"
#include "Shader.hpp"

class VertexArray;

#if defined PLATFORM_LINUX
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#elif defined PLATFORM_WINDOWS
#define ASSERT(x) if (!(x)) __debugbreak();
#else
#define ASSERT(X) 1
#endif
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