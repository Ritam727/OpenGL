#include "Test.hpp"

#include "imgui/imgui.h"

test::TestMenu::TestMenu(Test *&currentTestPointer)
    : m_currentTest(currentTestPointer)
{
}

void test::TestMenu::OnImGuiRender()
{
    for (std::pair<std::string, std::function<Test*()>> test : m_Tests)
    {
        if (ImGui::Button(test.first.c_str()))
            m_currentTest = test.second();
    }
}
