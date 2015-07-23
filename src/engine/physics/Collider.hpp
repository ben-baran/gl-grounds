#pragma once

#include <utility>
#include <glm/glm.hpp>

class RectangleCollider;
class GridCollider;
class PolygonCollider;
class Entity;

class Collider
{
private:
	static std::pair<double, double> intersection(RectangleCollider &a, glm::mat4 &mA, RectangleCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(RectangleCollider &a, glm::mat4 &mA, GridCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(RectangleCollider &a, glm::mat4 &mA, PolygonCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(PolygonCollider &a, glm::mat4 &mA, RectangleCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(PolygonCollider &a, glm::mat4 &mA, PolygonCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(double a[][2], int na,
												  double b[][2], int nb,
												  double axes[][2], int axesLength);
public:
	virtual int getClassID() = 0;
	virtual glm::vec4 boundingBox(glm::mat4 &transform) = 0;

	static const int LOW_ITERATIONS, HIGH_ITERATIONS;
	static std::pair<double, double> intersection(Collider &a, glm::mat4 &mA, Collider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(Entity &a, Entity &b);
};
