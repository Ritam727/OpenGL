#pragma once

#include "Renderer.hpp"
#include "Test.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test
{
    class TestZoom : public Test
    {
    public:
        TestZoom();
        ~TestZoom();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        float m_Zoom;
        glm::mat4 m_Proj;
        glm::mat4 m_Model;

        std::unique_ptr<VertexArray> m_Array;
        std::unique_ptr<VertexBuffer> m_Buffer;
        std::unique_ptr<VertexBufferLayout> m_Layout;
        std::unique_ptr<IndexBuffer> m_Index;
        std::unique_ptr<Shader> m_Shader;
    };
}