#include <src/engine/util/Res.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <src/engine/physics/RectangleCollider.hpp>
#include "SolidRectangle.hpp"

int SolidRectangle::attributes[] = {3, 3};
GLuint SolidRectangle::indices[] = {0, 1, 3,
                                    1, 2, 3};

float SolidRectangle::getX()
{
	return x;
}

float SolidRectangle::getY()
{
	return y;
}

float SolidRectangle::getWidth()
{
	return width;
}

float SolidRectangle::getHeight()
{
	return height;
}

float SolidRectangle::getR()
{
	return r;
}

long SolidRectangle::getG()
{
	return g;
}

float SolidRectangle::getB()
{
	return b;
}

SolidRectangle::SolidRectangle(float x, float y, float width, float height) : SolidRectangle(x, y, width, height, 1.0f, 1.0f, 1.0f) {}

SolidRectangle::SolidRectangle(float x, float y, float width, float height, float r, float g, float b)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
		, r(r)
		, g(g)
		, b(b)
{
    GLfloat vertices[24];
    vertices[0] = vertices[6] = x + width;
    vertices[1] = vertices[19] = y + height;
    vertices[12] = vertices[18] = x;
    vertices[7] = vertices[13] = y;

    for(int i = 0; i < 4; i++)
    {
        vertices[i * 6 + 2] = 0;
        vertices[i * 6 + 3] = r;
        vertices[i * 6 + 4] = g;
        vertices[i * 6 + 5] = b;
    }

    vao = new VAO(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);
    shader = Res::loadShader("res/shader/simple/color");
}

SolidRectangle::~SolidRectangle()
{
    vao->clean();
    delete vao;
}

void SolidRectangle::draw()
{
    shader->use();
    vao->draw();
}

void SolidRectangle::draw(Transform *transform)
{
    shader->use();
    glUniformMatrix4fv(shader->getLocation("transform"), 1, GL_FALSE, glm::value_ptr(transform->getMatrix()));
	vao->draw();
}

Collider &SolidRectangle::provideCollider()
{
    return *(new RectangleCollider(x, y, width, height));
}
