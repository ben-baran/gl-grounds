#pragma once

#include <GL/glew.h>
#include "Renderable.hpp"
#include "VAO.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class TexturedRectangle: public Renderable
{
	static int attributes[];
	static GLuint indices[];

	float x, y, width, height, tx0, ty0, tx1, ty1;
	VAO *vao;
	Shader *shader;
	Texture *texture;

	void constructVAO();

public:
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	float getTX0();
	float getTY0();
	float getTX1();
	float getTY1();

	TexturedRectangle(float width, float height, std::string &textureName);
	TexturedRectangle(float x, float y, float width, float height, std::string &textureName,
				   float tx0 = 0, float ty0 = 0, float tx1 = 1, float ty1 = 1,
				   double layer = 0);
	~TexturedRectangle();
	void setLayer(double layer);

	void render();
	void render(glm::mat4 transformMatrix);
	Collider &provideCollider();
};