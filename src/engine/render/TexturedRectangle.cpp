#include <src/engine/util/Res.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TexturedRectangle.hpp"
#include <src/engine/physics/RectangleCollider.hpp>

int TexturedRectangle::attributes[] = {3, 2};
GLuint TexturedRectangle::indices[] = {0, 1, 3,
									   1, 2, 3};

void TexturedRectangle::constructVAO()
{
	GLfloat vertices[20];
	vertices[0] = vertices[5] = x + width;
	vertices[1] = vertices[16] = y + height;
	vertices[10] = vertices[15] = x;
	vertices[6] = vertices[11] = y;

	vertices[3] = vertices[8] = tx1;
	vertices[4] = vertices[19] = ty1;
	vertices[13] = vertices[18] = tx0;
	vertices[9] = vertices[14] = ty0;

	for(int i = 0; i < 4; i++) vertices[i * 5 + 2] = (float) getLayer();

	vao = new VAO(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);
}

float TexturedRectangle::getX()
{
	return x;
}

float TexturedRectangle::getY()
{
	return y;
}

float TexturedRectangle::getWidth()
{
	return width;
}

float TexturedRectangle::getHeight()
{
	return height;
}

float TexturedRectangle::getTX0()
{
	return tx0;
}

float TexturedRectangle::getTY0()
{
	return ty0;
}

float TexturedRectangle::getTX1()
{
	return tx1;
}

float TexturedRectangle::getTY1()
{
	return ty1;
}

TexturedRectangle::TexturedRectangle(float width, float height, std::string textureName)
		: TexturedRectangle(-width / 2, -height / 2, width, height, textureName)
{}

TexturedRectangle::TexturedRectangle(float x, float y, float width, float height, std::string textureName, float tx0,
									 float ty0, float tx1, float ty1, double layer)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
		, tx0(tx0)
		, ty0(ty0)
		, tx1(tx1)
		, ty1(ty1)
{
	Renderable::setLayer(layer);
	texture = Res::loadTex(textureName);
	constructVAO();
	shader = Res::loadShader("res/shader/simple/texture");
}

TexturedRectangle::~TexturedRectangle()
{
	delete vao;
}

void TexturedRectangle::setLayer(double layer)
{
	Renderable::setLayer(layer);
	delete vao;
	constructVAO();
}

void TexturedRectangle::render()
{
	texture->use(*shader, "tex");
	shader->use();
	vao->draw();
}

void TexturedRectangle::render(glm::mat4 transformMatrix)
{
	texture->use(*shader, "tex");
	shader->use();
	glUniformMatrix4fv(shader->getLocation("transform"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
	vao->draw();
}

Collider &TexturedRectangle::provideCollider()
{
	return *(new RectangleCollider(x, y, width, height));
}
