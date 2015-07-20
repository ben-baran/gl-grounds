#pragma once

#include "Collider.hpp"

class RectangleCollider: public Collider
{
public:
	static const int CLASS_ID;
	int getClassID();
	RectangleCollider(double x, double y, double width, double height);
	double x, y, width, height;
};