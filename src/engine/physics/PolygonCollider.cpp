#include "PolygonCollider.hpp"

const int PolygonCollider::CLASS_ID = 2;

int PolygonCollider::getClassID()
{
	return CLASS_ID;
}

void PolygonCollider::getCoordinates(glm::mat4 &matrix, double (*coords)[2])
{
	for(int i = 0; i < points.size(); i++)
	{
		glm::vec4 point = matrix * glm::vec4(points[i].first, points[i].second, 0, 1);
		coords[i][0] = point.x;
		coords[i][1] = point.y;
	}
}

glm::vec4 PolygonCollider::boundingBox(glm::mat4 &matrix)
{
	double coords[points.size()][2];
	getCoordinates(matrix, coords);

	double minX = INFINITY, minY = INFINITY, maxX = -INFINITY, maxY = -INFINITY;
	for(int i = 0; i < points.size(); i++)
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

PolygonCollider::PolygonCollider(std::vector<std::pair<float, float>> &points)
	: points(points)
{}
