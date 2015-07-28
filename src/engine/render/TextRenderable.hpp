#pragma once

#include <GL/glew.h>
#include "Renderable.hpp"
#include "VAO.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class TextRenderable: public Renderable
{
	static int attributes[];
	static int startChar, charWidth, charHeight;
	static int nx, ny;

	float x, y, width, height;
	std::string text;
	VAO *vao;
	Shader *shader;
	Texture *fontTexture;

	void constructVAO();

public:
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	std::string getText();
	void setText(std::string text);

	TextRenderable(float x, float y, float width, float height, std::string text, double layer = 0);
	~TextRenderable();
	void setLayer(double layer);

	void render();
	void render(glm::mat4 transformMatrix);
	Collider &provideCollider();
};
