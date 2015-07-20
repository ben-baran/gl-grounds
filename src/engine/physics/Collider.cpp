#include "Collider.hpp"
#include "RectangleCollider.hpp"

const int Collider::LOW_ITERATIONS = 3, Collider::HIGH_ITERATIONS = 20;

std::pair<double, double> Collider::intersection(RectangleCollider &a, Transform &tA, RectangleCollider &b, Transform &tB)
{
	return std::make_pair(0.0, 0.0);
}

std::pair<double, double> Collider::intersection(Collider &a, Transform &tA, Collider &b, Transform &tB)
{
	if(a.getClassID() == RectangleCollider::CLASS_ID && b.getClassID() == RectangleCollider::CLASS_ID)
	{
		return intersection(*(static_cast<RectangleCollider *>(&a)), tA, *(static_cast<RectangleCollider *>(&b)), tB);
	}
}
