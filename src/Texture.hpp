#pragma once

#include <GL/glew.h>
#include <string>

#include "Shader.hpp"

struct Texture
{
    static constexpr GLenum UNIT[] = {GL_TEXTURE0,  GL_TEXTURE1,  GL_TEXTURE2,  GL_TEXTURE3,
                                      GL_TEXTURE4,  GL_TEXTURE5,  GL_TEXTURE6,  GL_TEXTURE7,
                                      GL_TEXTURE8,  GL_TEXTURE9,  GL_TEXTURE10, GL_TEXTURE11,
                                      GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15};
    int width, height;
    int unit = 0;
    GLuint id;

    void use(const Shader &shader, const std::string &name) const;
};