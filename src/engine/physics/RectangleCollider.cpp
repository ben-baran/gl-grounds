#include <algorithm>
#include "RectangleCollider.hpp"

const int RectangleCollider::CLASS_ID = 0;

RectangleCollider::RectangleCollider(double x, double y, double width, double height)
	: x(x)
	, y(y)
	, width(width)
	, height(height) {}

int RectangleCollider::getClassID() {
	return CLASS_ID;
}

void RectangleCollider::getCoordinates(glm::mat4 &matrix, double (*coords)[2]) {
	glm::vec4 p1 = matrix * glm::vec4(x, y, 0, 1);
	glm::vec4 p2 = matrix * glm::vec4(x, y + height, 0, 1);
	glm::vec4 p3 = matrix * glm::vec4(x + width, y + height, 0, 1);
	glm::vec4 p4 = matrix * glm::vec4(x + width, y, 0, 1);

	coords[0][0] = p1.x;
	coords[0][1] = p1.y;
	coords[1][0] = p2.x;
	coords[1][1] = p2.y;
	coords[2][0] = p3.x;
	coords[2][1] = p3.y;
	coords[3][0] = p4.x;
	coords[3][1] = p4.y;
}

glm::vec4 RectangleCollider::boundingBox(glm::mat4 &matrix) {
	double coords[4][2];
	getCoordinates(matrix, coords);
	double minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;
	for(int i = 0; i < 4; i++) {
		minX = std::min(minX, coords[i][0]);
		maxX = std::max(maxX, coords[i][0]);
		minY = std::min(minY, coords[i][1]);
		maxY = std::max(maxY, coords[i][1]);
	}

	glm::vec4 v;
	v.x = minX;
	v.y = minY;
	v.z = maxX;
	v.w = maxY;

	return v;
}

