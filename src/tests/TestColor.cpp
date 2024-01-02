#include "TestColor.hpp"

#include "imgui/imgui.h"

test::TestColor::TestColor()
    : m_Proj(glm::ortho(-640.0f, 640.0f, -320.0f, 320.0f, -1.0f, 1.0f)),
    m_Color(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f))
{
    std::vector<float> vertices({
        -100.0f, -100.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         100.0f, -100.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         100.0f,  100.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -100.0f,  100.0f, 1.0f, 1.0f, 1.0f, 0.0f
    });

    std::vector<unsigned int> indices({
        0, 1, 2,
        2, 3, 0
    });

    m_Array = std::make_unique<VertexArray>();
    m_Buffer = std::make_unique<VertexBuffer>(vertices.data(), 4 * 6 * sizeof(float));
    m_Layout = std::make_unique<VertexBufferLayout>();
    m_Layout->Push<float>(2);
    m_Layout->Push<float>(4);
    m_Array->AddBuffer(*m_Buffer, *m_Layout);
    m_Index = std::make_unique<IndexBuffer>(indices.data(), 6);

    m_Shader = std::make_unique<Shader>("res/shaders/Color.glsl");
}

test::TestColor::~TestColor()
{
}

void test::TestColor::OnUpdate(float deltaTime)
{
}

void test::TestColor::OnRender()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;

    {
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", m_Proj);
        m_Shader->SetUniform4f("u_Color", m_Color);
        renderer.Draw(*m_Array, *m_Index, *m_Shader);
    }
}

void test::TestColor::OnImGuiRender()
{
    ImGui::SliderFloat("Transparency", &m_Color.w, 0.0f, 1.0f);
}
