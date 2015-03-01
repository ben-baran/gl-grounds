#include "VAO.h"
#include <GL/glew.h>

VAO::VAO(GLfloat data[], int dataSize, GLuint indices[], int indicesSize, int attributes[], int attributesLength, GLenum usage)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, usage);

    for(int i = 0; i < attributesLength; i++) sum += attributes[i];

    for(int i = 0; i < attributesLength; i++)
    {
        glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, sum * sizeof(GLfloat), (GLvoid *) (attributes[i] * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

void VAO::draw()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, sum, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}