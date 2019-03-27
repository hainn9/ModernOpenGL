#ifndef OPENGL_DEBUG_H
#define OPENGL_DEBUG_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>
//Solution for fix warning when casting to void*
#define INT2VOIDP(x) (void*)(uintptr_t)(x)
//---------------------------------------------
#define ASSERT(x) if((!x)) asm("int $3")
#define GLCall(x) GLClearError(); \
    x;\
    ASSERT(GLLogCall(#x, __FUNCTION__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

#endif // OPENGL_DEBUG_H
