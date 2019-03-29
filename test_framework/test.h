#ifndef TEST_H
#define TEST_H

#include <vector>
#include <functional>

#include "opengl_debug.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "renderer.h"
#include "texture.h"

namespace test {

    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) { (void)deltaTime; }
        virtual void OnRender() {}
        virtual void OnImguiRender() {}
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test*& currentTest);

        void OnImguiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name)
        {
            m_Tests.push_back(std::make_pair(name, [](){ return new T(); }));
        }
    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
}

#endif // TEST_H
