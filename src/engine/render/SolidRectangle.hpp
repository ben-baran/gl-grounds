#pragma once

#include "VAO.hpp"
#include "Shader.hpp"
#include "Transform.hpp"
#include "Renderable.hpp"

class SolidRectangle: public Renderable
{
private:
    static int attributes[];
    static GLuint indices[];

    VAO *vao;
    Shader *shader;

public:
    SolidRectangle(float x, float y, float width, float height);
    SolidRectangle(float x, float y, float width, float height, float r, float g, float b);
    ~SolidRectangle();
    void draw();
    void draw(Transform *transform);
    Collider provideCollider();
};