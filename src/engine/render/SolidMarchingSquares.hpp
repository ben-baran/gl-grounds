#pragma once

#include "Renderable.hpp"
#include "VAO.hpp"
#include "Shader.hpp"

class SolidMarchingSquares: public Renderable
{
private:
	static int attributes[];
	VAO *vao;
	Shader *shader;

	std::vector<std::vector<int>> map;
	int nx, ny;
	double startX, startY, cellWidth, cellHeight;
	float r, g, b;

	void constructVAO();
public:

	static std::vector<std::vector<std::pair<double, double>>> partCoordinates;
	static std::vector<std::vector<int>> partIndices;

	SolidMarchingSquares(std::vector<std::vector<bool>> &baseMap, int nx, int ny,
						 double startX, double startY, double cellWidth, double cellHeight,
						 float r = 1.0f, float g = 1.0f, float b = 1.0f, double layer = 0);
	~SolidMarchingSquares();

	void setLayer(double layer);
	void render();
	void render(glm::mat4 transformMatrix);
	Collider &provideCollider();

	std::vector<std::vector<int>> &getMap();
};
