#include "MarchingSquaresCollider.hpp"

const int MarchingSquaresCollider::CLASS_ID = 3;

int MarchingSquaresCollider::getClassID()
{
	return CLASS_ID;
}

MarchingSquaresCollider::MarchingSquaresCollider(std::vector<std::vector<int>> &map, int nx, int ny, double startX,
												 double startY, double cellWidth, double cellHeight)
	: map(map)
	, nx(nx)
	, ny(ny)
	, startX(startX)
	, startY(startY)
	, cellWidth(cellWidth)
	, cellHeight(cellHeight)
	, width(cellWidth * nx)
	, height(cellHeight * ny)
{}

glm::vec4 MarchingSquaresCollider::boundingBox(glm::mat4 &matrix)
{
	double coords[4][2];

	glm::vec4 p1 = matrix * glm::vec4(startX, startY, 0, 1);
	glm::vec4 p2 = matrix * glm::vec4(startX, startY + height, 0, 1);
	glm::vec4 p3 = matrix * glm::vec4(startX + width, startY + height, 0, 1);
	glm::vec4 p4 = matrix * glm::vec4(startX + width, startY, 0, 1);

	coords[0][0] = p1.x;
	coords[0][1] = p1.y;
	coords[1][0] = p2.x;
	coords[1][1] = p2.y;
	coords[2][0] = p3.x;
	coords[2][1] = p3.y;
	coords[3][0] = p4.x;
	coords[3][1] = p4.y;

	double minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;
	for(int i = 0; i < 4; i++)
	{
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
