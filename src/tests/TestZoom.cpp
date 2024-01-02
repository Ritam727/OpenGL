#include "TestZoom.hpp"

#include <iostream>
#include "imgui/imgui.h"

test::TestZoom::TestZoom()
    : m_Zoom(0.1f), m_Proj(glm::perspective(glm::radians(60.0f), 2.0f, 0.1f, 50.0f))
{
    std::vector<float> vertices({
        -0.5f, -0.5f, -5.0f, 1.0f, 0.93f, 0.24f, 1.0f,
         0.5f, -0.5f, -5.0f, 1.0f, 0.93f, 0.24f, 1.0f,
         0.5f,  0.5f, -5.0f, 1.0f, 0.93f, 0.24f, 1.0f,
        -0.5f,  0.5f, -5.0f, 1.0f, 0.93f, 0.24f, 1.0f
    });

    std::vector<unsigned int> indices({
        0, 1, 2,
        2, 3, 0
    });

    m_Array = std::make_unique<VertexArray>();
    m_Buffer = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));
    m_Layout = std::make_unique<VertexBufferLayout>();
    m_Layout->Push<float>(3);
    m_Layout->Push<float>(4);
    m_Array->AddBuffer(*m_Buffer, *m_Layout);
    m_Index = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    m_Shader = std::make_unique<Shader>("res/shaders/Zoom.glsl");
}

test::TestZoom::~TestZoom()
{
}

void test::TestZoom::OnUpdate(float deltaTime)
{
}

void test::TestZoom::OnRender()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    
    m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, m_Zoom));

    Renderer renderer;
    {
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_Proj", m_Proj);
        m_Shader->SetUniformMat4f("u_Model", m_Model);
        renderer.Draw(*m_Array, *m_Index, *m_Shader);
    }
}

void test::TestZoom::OnImGuiRender()
{
    ImGui::SliderFloat("Zoom", &m_Zoom, -46.0f, 5.0f);
}
