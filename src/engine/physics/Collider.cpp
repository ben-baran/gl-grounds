#include "Collider.hpp"
#include "RectangleCollider.hpp"

const int Collider::LOW_ITERATIONS = 3, Collider::HIGH_ITERATIONS = 20;

std::pair<double, double> Collider::intersection(RectangleCollider &a, Transform &tA, RectangleCollider &b, Transform &tB)
{
	double aCoords[4][2], bCoords[4][2];
	a.getCoordinates(tA, aCoords);
	b.getCoordinates(tB, bCoords);

	double axes[4][2] = {
			{aCoords[0][0] - aCoords[1][0], aCoords[0][1] - aCoords[1][1]},
			{aCoords[1][0] - aCoords[2][0], aCoords[1][1] - aCoords[2][1]},
			{bCoords[0][0] - bCoords[1][0], bCoords[0][1] - bCoords[1][1]},
			{bCoords[1][0] - bCoords[2][0], bCoords[1][1] - bCoords[2][1]}
	};

	double smallestLength = INFINITY;
	auto smallestIntersection = std::make_pair(0.0, 0.0);

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

std::pair<double, double> Collider::intersection(Collider &a, Transform &tA, Collider &b, Transform &tB)
{
	if(a.getClassID() == RectangleCollider::CLASS_ID && b.getClassID() == RectangleCollider::CLASS_ID)
	{
		return intersection(*(static_cast<RectangleCollider *>(&a)), tA, *(static_cast<RectangleCollider *>(&b)), tB);
	}
}
