#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

#define ASSERT(x) if((!x)) asm("int $3")
#define GLCall(x) GLClearError(); \
    x;\
    ASSERT(GLLogCall(#x, __FUNCTION__, __LINE__))

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << " : " << line << std::endl;
        return false;
    }
    return true;
}

static unsigned int CompileSahder(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length*sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Fail to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileSahder(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileSahder(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    int result;
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &result));
    if(result == GL_FALSE)
    {
        int length;
        GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length*sizeof(char));
        GLCall(glGetProgramInfoLog(program, length, &length, message));
        std::cout << "Link shader error " << message << std::endl;
        GLCall(glDeleteProgram(program));
        return 0;
    }

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    return program;
}

static std::string ReadShaderFile(const char* filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    if(!fileStream.is_open())
    {
        std::cout  << "Cannot open file: " << filePath << std::endl;
        return "";
    }

    std::string line;
    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

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

//    std::cout << glGetString(GL_VERSION) << std::endl;

    // Define the viewport dimensions
    glViewport( 0, 0, screenWidth, screenHeight );

    // Set up vertex data (and buffer(s)) and attribute pointers
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f, // Bottom-Left
        0.5f, -0.5f, 0.0f, // Bottom-Right
        0.5f,  0.5f, 0.0f,  // Top-Right
        -0.5f, 0.5f, 0.0f  // Top-Left
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VBO, VAO, IBO;
    GLCall(glGenVertexArrays( 1, &VAO ));
    GLCall(glGenBuffers( 1, &VBO ));
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    GLCall(glBindVertexArray( VAO ));

    GLCall(glBindBuffer( GL_ARRAY_BUFFER, VBO ));
    GLCall(glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW ));

    GLCall(glEnableVertexAttribArray( 0 ));
    GLCall(glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void * ) 0 ));

    GLCall(glGenBuffers(1, &IBO));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    GLCall(glBindVertexArray(0)); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    //build and compile shader program
    std::string vertexShaderSource = ReadShaderFile("shader/shader.vert");
    std::string fragmentShaderSource = ReadShaderFile("shader/shader.frag");
    unsigned int shaderProgram = CreateShader(vertexShaderSource, fragmentShaderSource);

    float r = 0.0f;
    float delta = 0.05f;

    // Game loop
    while ( !glfwWindowShouldClose( window ) )
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents( );

        // Render
        // Clear the colorbuffer
        GLCall(glClear( GL_COLOR_BUFFER_BIT ));

        // Draw our first triangle
        GLCall(glUseProgram( shaderProgram ));
        GLCall(glBindVertexArray( VAO ));
        GLCall(glUniform4f(glGetUniformLocation(shaderProgram, "u_color"), r, 0.5, 0.2, 1.0));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr););
        if (r > 1.0f)
            delta = -0.05f;
        else if (r < 0.0f)
            delta = 0.05f;
        r += delta;

        GLCall(glBindVertexArray( 0 ));

        // Swap the screen buffers
        glfwSwapBuffers( window );
    }

    // Properly de-allocate all resources once they've outlived their purpose
    GLCall(glDeleteVertexArrays( 1, &VAO ));
    GLCall(glDeleteBuffers( 1, &VBO ));
    GLCall(glDeleteBuffers( 1, &IBO));

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );

    return EXIT_SUCCESS;
}



