#pragma once

#include "Renderer.hpp"

class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size, unsigned int mode = GL_STATIC_DRAW);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void UpdateData(unsigned int size, const void *data) const;
};