#include "test_clearcolor.h"

namespace test {

    Test_ClearColor::Test_ClearColor()
        :m_ClearColor{0.3f, 0.2f, 0.8f, 1.0f}
    {
    }

    Test_ClearColor::~Test_ClearColor()
    {

    }

    void Test_ClearColor::OnUpdate(float deltaTime)
    {
        (void)deltaTime;
    }

    void Test_ClearColor::OnRender()
    {
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT););
    }

    void Test_ClearColor::OnImguiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }

}


