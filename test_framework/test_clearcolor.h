#ifndef TEST_CLEARCOLOR_H
#define TEST_CLEARCOLOR_H

#include "test.h"

namespace test {

    class Test_ClearColor : public Test
    {
    public:
        Test_ClearColor();
        ~Test_ClearColor();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;

    private:
        float m_ClearColor[4];
    };

}

#endif // TEST_CLEARCOLOR_H
