#pragma once

#include "glm/glm.hpp"

class Vertex
{
public:
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    float TexId;

    Vertex()
        : Position({0.0f, 0.0f, 0.0f}), Color({1.0f, 1.0f, 1.0f, 1.0f}), TexCoord({0.0f, 0.0f}), TexId(0)
    {
    }

    Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 texCoord, float texId)
    {
        SetPosition(position);
        SetColor(color);
        SetTexCoord(texCoord);
        SetTexId(texId);
    }

    Vertex SetPosition(glm::vec3 position)
    {
        Position = position;
        return *this;
    }

    Vertex SetColor(glm::vec4 color)
    {
        Color = color;
        return *this;
    }

    Vertex SetTexCoord(glm::vec2 texCoord)
    {
        TexCoord = texCoord;
        return *this;
    }

    Vertex SetTexId(float texId)
    {
        TexId = texId;
        return *this;
    }
};