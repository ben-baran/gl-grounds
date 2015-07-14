#pragma once

#include <GL/glew.h>

class VAO
{
public:
    VAO(const GLfloat data[], const int &dataSize,
        const GLuint indices[], const int &indicesSize,
        const int attributes[], const int &attributesLength,
        const GLenum &usage);
    void draw();
    ~VAO();
private:
    int nVertices;
    GLuint vao, vbo, ebo;
};