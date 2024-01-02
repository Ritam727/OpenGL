#include "TestMultipleObjects.hpp"

#include "imgui/imgui.h"
#include "Vertex.hpp"

test::TestMultipleObjects::TestMultipleObjects()
    : m_Proj(glm::ortho(-640.0f, 640.0f, -320.0f, 320.0f, -1.0f, 1.0f)),
    m_X(std::vector<float>(2, 0.0f)), m_Y(std::vector<float>(2, 200.0f))
{
    
    std::vector<unsigned int> indices({
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4
    });

    m_Array = std::make_unique<VertexArray>();
    m_Buffer = std::make_unique<VertexBuffer>(nullptr, 1000 * sizeof(Vertex), GL_DYNAMIC_DRAW);
    m_Layout = std::make_unique<VertexBufferLayout>();
    m_Layout->Push<float>(3);
    m_Layout->Push<float>(4);
    m_Layout->Push<float>(2);
    m_Layout->Push<float>(1);
    m_Array->AddBuffer(*m_Buffer, *m_Layout);
    m_Index = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    m_Shader = std::make_unique<Shader>("res/shaders/Multiple.glsl");
    m_Shader->Bind();
    m_Texture = std::make_unique<Texture>("res/textures/Naruto_Baryon.png");
    m_Texture->Bind(1);

    m_Shader->SetUniform1i("u_Texture", 1);
}

test::TestMultipleObjects::~TestMultipleObjects()
{
}

void test::TestMultipleObjects::OnUpdate(float deltaTime)
{
    std::vector<Vertex> vertices({
        Vertex().SetPosition({m_X[1] - 50.0f, m_Y[1] - 50.0f, 1.0f}).SetTexId(1.1f).SetTexCoord({0.0f, 0.0f}),
        Vertex().SetPosition({m_X[1] + 50.0f, m_Y[1] - 50.0f, 1.0f}).SetTexId(1.1f).SetTexCoord({1.0f, 0.0f}),
        Vertex().SetPosition({m_X[1] + 50.0f, m_Y[1] + 50.0f, 1.0f}).SetTexId(1.1f).SetTexCoord({1.0f, 1.0f}),
        Vertex().SetPosition({m_X[1] - 50.0f, m_Y[1] + 50.0f, 1.0f}).SetTexId(1.1f).SetTexCoord({0.0f, 1.0f}),
        Vertex().SetPosition({m_X[0] - 50.0f, m_Y[0] - 50.0f, 1.0f}).SetColor({1.0f, 0.93f, 0.24f, 1.0f}),
        Vertex().SetPosition({m_X[0] + 50.0f, m_Y[0] - 50.0f, 1.0f}).SetColor({1.0f, 0.93f, 0.24f, 1.0f}),
        Vertex().SetPosition({m_X[0] + 50.0f, m_Y[0] + 50.0f, 1.0f}).SetColor({1.0f, 0.93f, 0.24f, 1.0f}),
        Vertex().SetPosition({m_X[0] - 50.0f, m_Y[0] + 50.0f, 1.0f}).SetColor({1.0f, 0.93f, 0.24f, 1.0f}),
    });

    m_Buffer->Bind();
    m_Buffer->UpdateData(vertices.size() * sizeof(Vertex), vertices.data());
}

void test::TestMultipleObjects::OnRender()
{
    Renderer renderer;

    {
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", m_Proj);
        renderer.Draw(*m_Array, *m_Index, *m_Shader);
    }
}

void test::TestMultipleObjects::OnImGuiRender()
{
    ImGui::SliderFloat2("Translation X", m_X.data(), -640.0f, 640.0f);
    ImGui::SliderFloat2("Translation Y", m_Y.data(), -360.0f, 360.0f);
}
