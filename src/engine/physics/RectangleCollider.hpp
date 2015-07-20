#pragma once

#include "Collider.hpp"

struct RectangleCollider: public Collider
{
	RectangleCollider(double x, double y, double width, double height);
	double x, y, width, height;
};