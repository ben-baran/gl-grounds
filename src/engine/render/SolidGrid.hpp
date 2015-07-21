#pragma once

#include "Renderable.hpp"
#include "VAO.hpp"

using std::vector;

class SolidGrid: public Renderable
{
private:
	static int attributes[];
	VAO *vao;
	Shader *shader;
public:
	SolidGrid(vector<vector<bool>> &map, int nx, int ny,
			  double startX, double startY, double cellWidth, double cellHeight,
			  float r = 1.0f, float g = 1.0f, float b = 1.0f, double layer = 0);
	void render();
	void render(glm::mat4 transformMatrix);
	Collider &provideCollider();
};