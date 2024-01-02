#pragma once

#include "Test.hpp"

#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"

#include <memory>

namespace test
{
    class TestTexture2D : public Test
    {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<IndexBuffer> m_Index;
        std::unique_ptr<Texture> m_TextureA;
        std::unique_ptr<Texture> m_TextureB;
        std::unique_ptr<VertexBuffer> m_Buffer;
        std::unique_ptr<VertexBufferLayout> m_Layout;

        glm::mat4 m_Proj;
        glm::mat4 m_View;
        glm::vec3 m_TranslationA, m_TranslationB;
    };
}