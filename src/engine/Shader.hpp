#pragma once

#include <string>
#include <GL/glew.h>
#include <unordered_map>

class Shader
{
private:
    GLuint program;
    std::unordered_map<std::string, GLuint> uniforms;
public:
    Shader(const std::string &vsource, const std::string &fsource);
    void use();
    void clean();
    GLint getLocation(const std::string &name) const;
};