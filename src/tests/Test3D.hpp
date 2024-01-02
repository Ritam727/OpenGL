#pragma once

#include "Renderer.hpp"
#include "Test.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Vertex.hpp"

#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include "imgui/imgui.h"

namespace test
{
    class Test3D : public Test
    {
    public:
        Test3D();
        ~Test3D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        glm::mat4 m_Proj;
        glm::mat4 m_View;
        glm::mat4 m_Model;
        float m_X, m_Y, m_Z;
        float m_Zoom;

        std::unique_ptr<VertexArray> m_Array;
        std::unique_ptr<VertexBuffer> m_Buffer;
        std::unique_ptr<VertexBufferLayout> m_Layout;
        std::unique_ptr<IndexBuffer> m_Index;
        std::unique_ptr<Shader> m_Shader;
    };
}