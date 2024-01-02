#pragma once

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "Test.hpp"
#include "Texture.hpp"

#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    class TestMultipleObjects : public Test
    {
    public:
        TestMultipleObjects();
        ~TestMultipleObjects();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        std::unique_ptr<VertexArray> m_Array;
        std::unique_ptr<VertexBuffer> m_Buffer;
        std::unique_ptr<VertexBufferLayout> m_Layout;
        std::unique_ptr<IndexBuffer> m_Index;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj;
        std::vector<float> m_X, m_Y;
    };
}