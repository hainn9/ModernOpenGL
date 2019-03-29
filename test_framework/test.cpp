#include "test.h"

namespace test {

    TestMenu::TestMenu(test::Test *&currentTest)
        :m_CurrentTest(currentTest)
    {
    }

    void TestMenu::OnImguiRender()
    {
        for(auto& test : m_Tests)
        {
            if(ImGui::Button(test.first.c_str()))
                m_CurrentTest = test.second();
        }
    }

}
