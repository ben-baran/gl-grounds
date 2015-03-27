#pragma once

#include <GL/glew.h>

struct Texture
{
    int width, height;
    GLuint id;

    void use() const
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }
};