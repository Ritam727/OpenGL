#pragma once

#include <vector>
#include "Renderer.hpp"

struct VertexBufferLayoutElement
{
    unsigned int type;
    unsigned int count;
    bool normalized;

    static unsigned int GetSizeOfElement(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT : return sizeof(GLfloat);
            case GL_UNSIGNED_INT : return sizeof(GLuint);
            case GL_UNSIGNED_BYTE : return sizeof(GLubyte);
        }
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferLayoutElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0) {}

    template<typename T>
    void Push(unsigned int count)
    {
        static_assert(true);
    }

    inline const std::vector<VertexBufferLayoutElement> GetElements() const
    {
        return m_Elements;
    }

    inline unsigned int GetStride() const
    {
        return m_Stride;
    }
};

template<> inline
void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * VertexBufferLayoutElement::GetSizeOfElement(GL_FLOAT);
}

template<> inline
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += count * VertexBufferLayoutElement::GetSizeOfElement(GL_UNSIGNED_INT);
}

template<> inline
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += count * VertexBufferLayoutElement::GetSizeOfElement(GL_UNSIGNED_BYTE);
}