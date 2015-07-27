#include <src/engine/util/Res.hpp>
#include "TexturedRectangle.hpp"

int TexturedRectangle::attributes[] = {3, 3, 2};
GLuint TexturedRectangle::indices[] = {0, 1, 3,
									   1, 2, 3};

void TexturedRectangle::constructVAO()
{

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

TexturedRectangle::TexturedRectangle(float width, float height, std::string &textureName)
	: TexturedRectangle(-width / 2, -height / 2, width, height, textureName)
{}

TexturedRectangle::TexturedRectangle(float x, float y, float width, float height, std::string &textureName, float tx0,
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

}

void TexturedRectangle::setLayer(double layer)
{
	Renderable::setLayer(layer);
}

void TexturedRectangle::render()
{

}

void TexturedRectangle::render(glm::mat4 transformMatrix)
{

}

Collider &TexturedRectangle::provideCollider()
{
	return <#initializer#>;
}
