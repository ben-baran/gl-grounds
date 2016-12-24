#pragma once

#include <vector>
#include "Collider.hpp"

class PolygonCollider: public Collider
{
public:
	static const int CLASS_ID;
	int getClassID();
	std::vector<std::pair<float, float>> &points;
	void getCoordinates(glm::mat4 &matrix, double coords[][2]);
	glm::vec4 boundingBox(glm::mat4 &matrix);

	PolygonCollider(std::vector<std::pair<float, float>> &points);
	~PolygonCollider(){};
};