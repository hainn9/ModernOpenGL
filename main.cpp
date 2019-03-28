#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbufferlayout.h"
#include "shader.h"
#include "renderer.h"
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Window dimensions
const int WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit( );

    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "OpenGL Window", nullptr, nullptr );

    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent( window );
    glfwSwapInterval(1);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    GLCall(glViewport( 0, 0, screenWidth, screenHeight ));
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
    {
        VertexArray vao;

        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        vao.Bind();

        VertexBuffer vbo(vertices, sizeof(vertices));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        vao.AddBuffer(vbo, layout);

        unsigned int number_of_index = sizeof(indices)/sizeof(unsigned int);
        IndexBuffer ibo(indices, number_of_index);

        //Setting MVP matrix
        glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);

        //Build and compile shader program
        Shader shaderProgram("res/shader/shader.vert", "res/shader/shader.frag");
        shaderProgram.Bind();
        shaderProgram.SetUniform4f("u_color", 0.8, 0.5, 0.2, 1.0);
        shaderProgram.SetUniformMat4f("u_MVP", proj);

        //Load Texture
        Texture texture("res/texture/image.png");

        vbo.UnBind(); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
        ibo.UnBind();
        vao.UnBind(); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
        shaderProgram.UnBind();

        Renderer renderer;

        // Game loop
        while ( !glfwWindowShouldClose( window ) )
        {
            // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
            glfwPollEvents( );

            // Render
            // Clear the colorbuffer
            renderer.Clear();

            // Draw our first triangle
            shaderProgram.Bind();
            texture.Bind(0);
            shaderProgram.SetUniform1i("u_Texture", 0);

            renderer.Draw(vao, ibo, shaderProgram);

            // Swap the screen buffers
            glfwSwapBuffers( window );
        }
    }
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );

    return EXIT_SUCCESS;
}



