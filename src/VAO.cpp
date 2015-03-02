#include "VAO.h"

VAO::VAO(GLfloat data[], int dataSize, GLuint indices[], int indicesSize, int attributes[], int attributesLength, GLenum usage)
{
    nVertices = indicesSize;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, usage);

    int sum = 0;
    for(int i = 0; i < attributesLength; i++) sum += attributes[i];

    int offset = 0;
    for(int i = 0; i < attributesLength; i++)
    {
        glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, sum * sizeof(GLfloat), (GLvoid *) (offset * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
        offset += attributes[i];
    }
    glBindVertexArray(0);
}

void VAO::draw()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, nVertices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}