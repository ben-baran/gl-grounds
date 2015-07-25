#pragma once

#include "Renderable.hpp"
#include "VAO.hpp"

class SolidGrid: public Renderable
{
private:
	static int attributes[];
	VAO *vao;
	Shader *shader;

	std::vector<std::vector<bool>> map;
	int nx, ny;
	double startX, startY, cellWidth, cellHeight;
	float r, g, b;

	void constructVAO();

public:
	SolidGrid(std::vector<std::vector<bool>> &map, int nx, int ny,
			  double startX, double startY, double cellWidth, double cellHeight,
			  float r = 1.0f, float g = 1.0f, float b = 1.0f, double layer = 0);
	~SolidGrid();

	void setLayer(double layer);
	void render();
	void render(glm::mat4 transformMatrix);
	Collider &provideCollider();
};