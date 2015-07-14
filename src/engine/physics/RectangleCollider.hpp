#pragma once

#include "Collider.hpp"

class RectangleCollider: public Collider
{
public:
	RectangleCollider(double x, double y, double width, double height);
};