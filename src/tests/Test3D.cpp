#include "Test3D.hpp"

test::Test3D::Test3D()
    : m_Proj(glm::perspective(glm::radians(45.0f), 2.0f, 0.1f, 50.0f)),
    m_Model(glm::mat4(1.0f)), m_Zoom(0.0f), m_X(0.0f), m_Y(0.0f), m_Z(0.0f)
{
    std::vector<Vertex> vertices({
        Vertex().SetPosition({-0.5f, -0.5f, -0.5f}).SetColor({1.0f, 0.0f, 0.0f, 1.0f}),
        Vertex().SetPosition({ 0.5f, -0.5f, -0.5f}).SetColor({0.0f, 1.0f, 0.0f, 1.0f}),
        Vertex().SetPosition({ 0.5f,  0.5f, -0.5f}).SetColor({0.0f, 0.0f, 1.0f, 1.0f}),
        Vertex().SetPosition({-0.5f,  0.5f, -0.5f}).SetColor({1.0f, 1.0f, 1.0f, 1.0f}),
        Vertex().SetPosition({-0.5f, -0.5f,  0.5f}).SetColor({1.0f, 0.0f, 0.0f, 1.0f}),
        Vertex().SetPosition({ 0.5f, -0.5f,  0.5f}).SetColor({0.0f, 1.0f, 0.0f, 1.0f}),
        Vertex().SetPosition({ 0.5f,  0.5f,  0.5f}).SetColor({0.0f, 0.0f, 1.0f, 1.0f}),
        Vertex().SetPosition({-0.5f,  0.5f,  0.5f}).SetColor({1.0f, 1.0f, 1.0f, 1.0f}),
    });

    std::vector<unsigned int> indices({
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 5, 5, 4, 0,
        3, 2, 6, 6, 7, 3,
        2, 1, 5, 5, 6, 2,
        0, 3, 7, 7, 4, 0
    });

    m_Array = std::make_unique<VertexArray>();
    m_Buffer = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex), GL_DYNAMIC_DRAW);
    m_Layout = std::make_unique<VertexBufferLayout>();
    m_Layout->Push<float>(3);
    m_Layout->Push<float>(4);
    m_Layout->Push<float>(2);
    m_Layout->Push<float>(1);
    m_Array->AddBuffer(*m_Buffer, *m_Layout);
    m_Index = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    m_Shader = std::make_unique<Shader>("res/shaders/3D.glsl");
}

test::Test3D::~Test3D()
{
}

void test::Test3D::OnUpdate(float deltaTime)
{
    m_Model = glm::mat4_cast(glm::quat({ glm::radians(m_X), glm::radians(m_Y), glm::radians(m_Z) }));
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, m_Zoom - 5.0f));
}

void test::Test3D::OnRender()
{
    Renderer renderer;
    {
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_Proj", m_Proj);
        m_Shader->SetUniformMat4f("u_View", m_View);
        m_Shader->SetUniformMat4f("u_Model", m_Model);
        renderer.Draw(*m_Array, *m_Index, *m_Shader);
    }
}

void test::Test3D::OnImGuiRender()
{
    ImGui::SliderFloat("Angle X", &m_X, 0.0f, 360.0f);
    ImGui::SliderFloat("Angle Y", &m_Y, 0.0f, 360.0f);
    ImGui::SliderFloat("Angle Z", &m_Z, 0.0f, 360.0f);
    ImGui::SliderFloat("Zoom", &m_Zoom, -46.0f, 6.0f);
}
