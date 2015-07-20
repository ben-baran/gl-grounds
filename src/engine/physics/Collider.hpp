#pragma once

#include <utility>
#include "RectangleCollider.hpp"

class Collider
{
private:
	static std::pair<double, double> intersectData(RectangleCollider a, RectangleCollider b);
public:
	static void collideAgainst(Collider base, Collider against);
};
