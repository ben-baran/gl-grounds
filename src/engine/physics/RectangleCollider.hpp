#pragma once

#include "Collider.hpp"

class RectangleCollider: public Collider
{
public:
	static const int CLASS_ID;
	int getClassID();
	double x, y, width, height;

	RectangleCollider(double x, double y, double width, double height);
	void getCoordinates(glm::mat4 &matrix, double coords[4][2]);
	glm::vec4 boundingBox(glm::mat4 &matrix);
	~RectangleCollider(){};
};