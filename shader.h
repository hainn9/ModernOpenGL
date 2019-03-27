#ifndef SHADER_H
#define SHADER_H

#include "opengl_debug.h"
#include <string>
#include <fstream>

class Shader
{
public:
    Shader(const char* vsPath, const char* fsPath);
    ~Shader();

    void Bind() const;
    void UnBind() const;

    void SetUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3);
private:
    unsigned int m_rendererID;

private:
    std::string ReadShaderFile(const char* filePath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

#endif // SHADER_H
