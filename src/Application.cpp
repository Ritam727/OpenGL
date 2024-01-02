#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.hpp"
#include "tests/TestTexture2D.hpp"
#include "tests/TestColor.hpp"
#include "tests/TestZoom.hpp"
#include "tests/TestMultipleObjects.hpp"
#include "tests/Test3D.hpp"

int main(void)
{
    GLFWwindow *window;
    int *p = nullptr;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    window = glfwCreateWindow(1280, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cout << "Error" << std::endl;
    {

        GLCall(glClearDepth(1.0f));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDisable(GL_CULL_FACE));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        Renderer renderer;
        ImGui::CreateContext();

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");

        test::Test *currentTest = nullptr;
        test::TestMenu *testMenu = new test::TestMenu(currentTest);
        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
        testMenu->RegisterTest<test::TestColor>("Rainbow");
        testMenu->RegisterTest<test::TestZoom>("Zoom");
        testMenu->RegisterTest<test::TestMultipleObjects>("Multiple");
        testMenu->RegisterTest<test::Test3D>("3D");

        currentTest = testMenu;

        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                currentTest->OnImGuiRender();
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                ImGui::End();
            }

            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        if (currentTest != testMenu)
            delete testMenu;
        delete currentTest;
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}