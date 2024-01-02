#include "TestTexture2D.hpp"

#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"

#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

test::TestTexture2D::TestTexture2D()
    : m_Proj(glm::ortho(-640.0f, 640.0f, -320.0f, 320.0f, -1.0f, 1.0f)),
    m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
    m_TranslationA(200, 0, 0), m_TranslationB(400, 0, 0)
{
    std::vector<float> positions({
        -50.0f, -50.0f, 0.0f, 0.0f, 0.1f,
         50.0f, -50.0f, 1.0f, 0.0f, 0.1f,
         50.0f,  50.0f, 1.0f, 1.0f, 0.1f,
        -50.0f,  50.0f, 0.0f, 1.0f, 0.1f,
        150.0f, -50.0f, 0.0f, 0.0f, 1.1f,
        250.0f, -50.0f, 1.0f, 0.0f, 1.1f,
        250.0f,  50.0f, 1.0f, 1.0f, 1.1f,
        150.0f,  50.0f, 0.0f, 1.0f, 1.1f,
    });

    std::vector<unsigned int> indices({
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4
    });

    m_VAO = std::make_unique<VertexArray>();
    m_Buffer = std::make_unique<VertexBuffer>(positions.data(), positions.size() * sizeof(float));
    m_Layout = std::make_unique<VertexBufferLayout>();
    m_Layout->Push<float>(2);
    m_Layout->Push<float>(2);
    m_Layout->Push<float>(1);
    m_VAO->AddBuffer(*m_Buffer, *m_Layout);
    m_Index = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    m_Shader = std::make_unique<Shader>("res/shaders/Texture.glsl");
    m_Shader->Bind();
    m_TextureA = std::make_unique<Texture>("res/textures/Naruto_Baryon.png");
    m_TextureA->Bind(1);
    m_TextureB = std::make_unique<Texture>("res/textures/img.png");
    m_TextureB->Bind(2);

    std::vector<int> arr({ 1, 2 });
    m_Shader->SetUniform2iv("u_Texture", arr.data());
}

test::TestTexture2D::~TestTexture2D()
{
}

void test::TestTexture2D::OnUpdate(float deltaTime)
{
}

void test::TestTexture2D::OnRender()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_Index, *m_Shader);
    }
}

void test::TestTexture2D::OnImGuiRender()
{
    ImGui::SliderFloat3("Translation A", &m_TranslationA.x, -640.0f, 640.0f);
    ImGui::SliderFloat3("Translation B", &m_TranslationB.x, -640.0f, 640.0f);
}
