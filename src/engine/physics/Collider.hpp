#pragma once

#include <utility>
#include <src/engine/anim/Transform.hpp>
#include "RectangleCollider.hpp"

class Collider
{
private:
	static std::pair<double, double> intersection(RectangleCollider &a, Transform &tA, RectangleCollider &b, Transform &tB);
public:
	virtual int getClassID() = 0;

	static const int LOW_ITERATIONS, HIGH_ITERATIONS;
	static std::pair<double, double> intersection(Collider &a, Transform &tA, Collider &b, Transform &tB);
};
