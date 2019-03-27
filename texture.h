#ifndef TEXTURE_H
#define TEXTURE_H

#include "opengl_debug.h"
#include "stb_image.h"

class Texture
{
public:
    Texture(const char* path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void UnBind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }

private:
    int m_Width, m_Height, m_BPP;
    unsigned char* m_LocalBuffer;
    unsigned int m_rendererID;
};

#endif // TEXTURE_H
