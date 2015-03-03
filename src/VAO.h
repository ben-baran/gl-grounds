#pragma once

#include <GL/glew.h>

class VAO
{
public:
    VAO(GLfloat data[], int dataSize, GLuint indices[], int indicesSize, int attributes[], int attributesLength, GLenum usage);
    void draw();
    void clean();
private:
    int nVertices;
    GLuint vao, vbo, ebo;
};