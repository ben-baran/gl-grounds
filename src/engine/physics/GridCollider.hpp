#pragma once

#include <vector>
#include "Collider.hpp"

class GridCollider: public Collider
{
public:
	static const int CLASS_ID;
	int getClassID();

	std::vector<std::vector<bool>> &map;
	int nx, ny;
	double startX, startY, cellWidth, cellHeight, width, height;

	GridCollider(std::vector<std::vector<bool>> &map, int nx, int ny,
				 double startX, double startY, double cellWidth, double cellHeight);

	glm::vec4 boundingBox(glm::mat4 &matrix);
	~GridCollider(){};
};