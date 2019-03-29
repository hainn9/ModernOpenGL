#ifndef TEST_TEXTURE2D_H
#define TEST_TEXTURE2D_H

#include "test.h"
#include <memory>

namespace test {

    class Test_Texture2D : public Test
    {
    public:
        Test_Texture2D();
        ~Test_Texture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj, m_View;
        glm::vec3 m_Translation;
    };

}

#endif // TEST_TEXTURE2D_H
