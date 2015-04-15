#include "Texture.hpp"

constexpr GLenum Texture::UNIT[];

void Texture::use(const Shader &shader, const std::string &name) const
{
    glActiveTexture(UNIT[unit]);
    glBindTexture(GL_TEXTURE_2D, id);
    glUniform1i(shader.getLocation(name), unit);
}