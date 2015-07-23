#pragma once

#include <utility>
#include <glm/glm.hpp>

class RectangleCollider;
class GridCollider;
class Entity;

class Collider
{
private:
	static std::pair<double, double> intersection(RectangleCollider &a, glm::mat4 &mA, RectangleCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(RectangleCollider &a, glm::mat4 &mA, GridCollider &b, glm::mat4 &mB);
public:
	virtual int getClassID() = 0;
	virtual glm::vec4 boundingBox(glm::mat4 &transform) = 0;

	static const int LOW_ITERATIONS, HIGH_ITERATIONS;
	static std::pair<double, double> intersection(Collider &a, glm::mat4 &mA, Collider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(Entity &a, Entity &b);
};
