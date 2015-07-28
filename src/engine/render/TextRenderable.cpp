#include <string>
#include <sstream>
#include <src/engine/util/Res.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TextRenderable.hpp"
#include <src/engine/physics/RectangleCollider.hpp>
#include <iostream>

using std::string;

int TextRenderable::attributes[] = {3, 2};
int TextRenderable::startChar = 32, TextRenderable::charWidth = 32, TextRenderable::charHeight = 64;
int TextRenderable::nx = 16, TextRenderable::ny = 8;

void TextRenderable::constructVAO()
{
	GLfloat vertices[20 * text.length()];
	GLuint indices[6 * text.length()];

	for(int i = 0; i < text.length(); i++)
	{
		int charIndex = text[i] - startChar;
		float tx0 = (charIndex % nx) / float(nx), ty0 = (charIndex / nx) / float(ny);
		float tx1 = tx0 + 1.0f / nx, ty1 = ty0 + 1.0f / ny;

		std::cout << i << ": " << tx0 * 512 << ", " << ty0 * 512 << ", " << tx1 * 512 << ", " << ty1 * 512 << std::endl;

		int off = i * 20;
		vertices[off] = vertices[off + 5] = x + (i + 1) * width;
		vertices[off + 1] = vertices[off + 16] = y + height;
		vertices[off + 10] = vertices[off + 15] = x + i * width;
		vertices[off + 6] = vertices[off + 11] = y;

		vertices[off + 3] = vertices[off + 8] = tx1;
		vertices[off + 4] = vertices[off + 19] = ty0;
		vertices[off + 13] = vertices[off + 18] = tx0;
		vertices[off + 9] = vertices[off + 14] = ty1;

		for(int j = 0; j < 4; j++) vertices[off + j * 5 + 2] = (float) getLayer();

		indices[i * 6] = i * 4;
		indices[i * 6 + 1] = indices[i * 6 + 3] = i * 4 + 1;
		indices[i * 6 + 4] = i * 4 + 2;
		indices[i * 6 + 2] = indices[i * 6 + 5] = i * 4 + 3;
	}

	vao = new VAO(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);
}

float TextRenderable::getX()
{
	return x;
}

float TextRenderable::getY()
{
	return y;
}

float TextRenderable::getWidth()
{
	return width;
}

float TextRenderable::getHeight()
{
	return height;
}

string TextRenderable::getText()
{
	return text;
}

void TextRenderable::setText(string text)
{
	this->text = text;
	delete vao;
	constructVAO();
}

TextRenderable::TextRenderable(float x, float y, float width, float height, string text, double layer)
	: x(x)
	, y(y)
	, width(width)
	, height(height)
	, text(text)
{
	Renderable::setLayer(layer);
	fontTexture = Res::loadTex("res/SCPL.png");
	constructVAO();
	shader = Res::loadShader("res/shader/simple/ftexture");
}

TextRenderable::~TextRenderable()
{
	delete vao;
}

void TextRenderable::setLayer(double layer)
{
	Renderable::setLayer(layer);
}

void TextRenderable::render()
{
	fontTexture->use(*shader, "tex");
	shader->use();
	vao->draw();
}

void TextRenderable::render(glm::mat4 transformMatrix)
{
	fontTexture->use(*shader, "tex");
	shader->use();
	glUniformMatrix4fv(shader->getLocation("transform"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
	vao->draw();
}

Collider &TextRenderable::provideCollider()
{
	return *(new RectangleCollider(x, y, width * text.length(), height));
}
