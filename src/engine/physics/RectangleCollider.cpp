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

void RectangleCollider::getCoordinates(Transform &t, double (*coords)[2])
{
	glm::mat4 matrix = t.getMatrix();
	glm::vec4 p1 = matrix * glm::vec4(x, y, 0, 1);
	glm::vec4 p2 = matrix * glm::vec4(x, y + height, 0, 1);
	glm::vec4 p3 = matrix * glm::vec4(x + width, y + height, 0, 1);
	glm::vec4 p4 = matrix * glm::vec4(x + width, y, 0, 1);

	coords[0][0] = p1.a;
	coords[0][1] = p1.b;
	coords[1][0] = p2.a;
	coords[1][1] = p2.b;
	coords[2][0] = p3.a;
	coords[2][1] = p3.b;
	coords[3][0] = p4.a;
	coords[4][1] = p4.b;
}
