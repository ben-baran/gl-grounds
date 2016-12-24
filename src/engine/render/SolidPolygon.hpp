#pragma once

#include <GL/glew.h>
#include "Renderable.hpp"
#include "Shader.hpp"
#include "VAO.hpp"

class SolidPolygon: public Renderable
{
private:
	static int attributes[];

	std::vector<std::pair<float, float>> points;
	float r, b, g;
	VAO *vao;
	Shader *shader;

	void constructVAO();

public:
	SolidPolygon(std::vector<std::pair<float, float>> &points, float r = 1.0f, float g = 1.0f, float b = 1.0f, double layer = 0);
	~SolidPolygon();

	void setLayer(double layer);
	void render();
	void render(glm::mat4 transformMatrix);
	Collider &provideCollider();
};