#include "RectangleCollider.hpp"

const int RectangleCollider::CLASS_ID = 0;

RectangleCollider::RectangleCollider(double x, double y, double width, double height)
	: x(x)
	, y(y)
	, width(width)
	, height(height)
{}

int RectangleCollider::getClassID()
{
	return CLASS_ID;
}
