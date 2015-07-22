#include <glm/detail/func_matrix.hpp>
#include <algorithm>
#include <src/engine/util/KeyHandler.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Collider.hpp"
#include "RectangleCollider.hpp"
#include "GridCollider.hpp"

const int Collider::LOW_ITERATIONS = 3, Collider::HIGH_ITERATIONS = 20;

std::pair<double, double> Collider::intersection(RectangleCollider &a, glm::mat4 &mA, RectangleCollider &b, glm::mat4 &mB)
{
	double aCoords[4][2], bCoords[4][2];
	a.getCoordinates(mA, aCoords);
	b.getCoordinates(mB, bCoords);

	double axes[4][2] = {
			{aCoords[0][0] - aCoords[1][0], aCoords[0][1] - aCoords[1][1]},
			{aCoords[1][0] - aCoords[2][0], aCoords[1][1] - aCoords[2][1]},
			{bCoords[0][0] - bCoords[1][0], bCoords[0][1] - bCoords[1][1]},
			{bCoords[1][0] - bCoords[2][0], bCoords[1][1] - bCoords[2][1]}
	};

	double smallestLength = INFINITY;
	std::pair<double, double> smallestIntersection;

	for(int i = 0; i < 4; i++)
	{
		double length = std::sqrt(axes[i][0] * axes[i][0] + axes[i][1] * axes[i][1]);
		double axisX = axes[i][0] / length, axisY = axes[i][1] / length;
		double aMin = INFINITY, aMax = -INFINITY, bMin = INFINITY, bMax = -INFINITY;

		for(int j = 0; j < 4; j++)
		{
			double aVal = axisX * aCoords[j][0] + axisY * aCoords[j][1];
			double bVal = axisX * bCoords[j][0] + axisY * bCoords[j][1];
			aMin = std::min(aMin, aVal);
			aMax = std::max(aMax, aVal);
			bMin = std::min(bMin, bVal);
			bMax = std::max(bMax, bVal);
		}

		if(aMin > bMax || aMax < bMin) return std::make_pair(0.0, 0.0);
		double length1 = aMax - bMin, length2 = bMax - aMin;
		if(length1 < smallestLength && length1 < length2)
		{
			smallestLength = length1;
			length1 = -length1;
			smallestIntersection.first = axisX * length1;
			smallestIntersection.second = axisY * length1;
		}
		else if(length2 < smallestLength)
		{
			smallestLength = length2;
			smallestIntersection.first = axisX * length2;
			smallestIntersection.second = axisY * length2;
		}
	}

	return smallestIntersection;
}

std::pair<double, double> Collider::intersection(RectangleCollider &a, glm::mat4 &mA, GridCollider &b, glm::mat4 &mB)
{
	std::pair<double, double> intersect;

	glm::mat4 adjust = glm::inverse(mB) * mA;
	glm::vec4 aBB = a.boundingBox(adjust);
	int minX = std::max(0, (int) ((aBB.x - b.startX) / b.cellWidth));
	int maxX = std::min(b.nx - 1, (int) ((aBB.z - b.startX) / b.cellWidth));
	int minY = std::max(0, (int) ((aBB.y - b.startY) / b.cellHeight));
	int maxY = std::min(b.ny - 1, (int) ((aBB.w - b.startX) / b.cellHeight));

	glm::mat4 correctedMatrix = mA;
	for(int i = minX; i <= maxX; i++) for(int j = minY; j <= maxY; j++) if(b.map[i][j])
	{
		RectangleCollider currentCollider(b.startX + b.cellWidth * i,
										  b.startY + b.cellHeight * j,
										  b.cellWidth, b.cellHeight);
		auto curIntersection = intersection(a, correctedMatrix, currentCollider, mB);
		intersect.first += curIntersection.first;
		intersect.second += curIntersection.second;
		correctedMatrix = glm::translate(glm::mat4(),
										 glm::vec3((float) curIntersection.first,
												   (float) curIntersection.second,
												   0.0f))
						  * correctedMatrix;
	}

	return intersect;
}

std::pair<double, double> Collider::intersection(Collider &a, glm::mat4 &mA, Collider &b, glm::mat4 &mB)
{
	glm::vec4 aBox = a.boundingBox(mA), bBox = b.boundingBox(mB);
	if(aBox.x > bBox.z || aBox.z < bBox.x || aBox.y > bBox.w || aBox.w < bBox.y) return std::make_pair(0.0, 0.0);

	if(a.getClassID() == RectangleCollider::CLASS_ID && b.getClassID() == RectangleCollider::CLASS_ID)
	{
		return intersection(static_cast<RectangleCollider &>(a), mA, static_cast<RectangleCollider &>(b), mB);
	}

	if(a.getClassID() == RectangleCollider::CLASS_ID && b.getClassID() == GridCollider::CLASS_ID)
	{
		return intersection(static_cast<RectangleCollider &>(a), mA, static_cast<GridCollider &>(b), mB);
	}
}
