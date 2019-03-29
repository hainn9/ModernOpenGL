#include "test_texture2d.h"

namespace test {

Test_Texture2D::Test_Texture2D()
    :m_Proj(glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f)),
      m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f))),
      m_Translation(2.0f, 2.0f, 0.0f)
{
    GLCall(glEnable( GL_BLEND ));
    GLCall(glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ));
    // Set up vertex data (and buffer(s)) and attribute pointers
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// Bottom-Left
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,// Bottom-Right
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,// Top-Right
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // Top-Left
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    m_VAO = std::unique_ptr<VertexArray>(new VertexArray());
    m_VAO->Bind();
    m_VBO = std::unique_ptr<VertexBuffer>(new VertexBuffer(vertices, sizeof(vertices)));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VBO, layout);
    unsigned int number_of_index = sizeof(indices)/sizeof(unsigned int);
    m_IBO = std::unique_ptr<IndexBuffer>(new IndexBuffer(indices, number_of_index));

    m_Shader = std::unique_ptr<Shader>(new Shader("res/shader/shader.vert", "res/shader/shader.frag"));
    m_Shader->Bind();
    m_Texture = std::unique_ptr<Texture>(new Texture("res/texture/image.png"));

    m_VBO->UnBind();
    m_IBO->UnBind();
    m_VAO->UnBind();
    m_Shader->UnBind();
}

Test_Texture2D::~Test_Texture2D()
{

}

void Test_Texture2D::OnUpdate(float deltaTime)
{
    (void)deltaTime;
}

void Test_Texture2D::OnRender()
{
    Renderer renderer;
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
    glm::mat4 mvp = m_Proj * m_View * model;
    m_Shader->Bind();
    m_Texture->Bind(0);
    m_Shader->SetUniform1i("u_Texture", 0);
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
}

void Test_Texture2D::OnImguiRender()
{
    ImGui::SliderFloat3("Translation", &m_Translation.x, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}



}
