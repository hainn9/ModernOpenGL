#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "opengl_debug.h"

class VertexBuffer
{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};

#endif // VERTEXBUFFER_H
