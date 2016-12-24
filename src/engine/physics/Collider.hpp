#pragma once

#include <glm/glm.hpp>
#include <utility>

class RectangleCollider;
class GridCollider;
class MarchingSquaresCollider;
class PolygonCollider;
class Entity;

class Collider {
private:
	static std::pair<double, double> intersection(RectangleCollider &a, glm::mat4 &mA, RectangleCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(RectangleCollider &a, glm::mat4 &mA, GridCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(RectangleCollider &a, glm::mat4 &mA, PolygonCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(PolygonCollider &a, glm::mat4 &mA, RectangleCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(PolygonCollider &a, glm::mat4 &mA, PolygonCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(double a[][2], int na,
												  double b[][2], int nb,
												  double axes[][2], int axesLength);
	static std::pair<double, double> intersection(RectangleCollider &a, glm::mat4 &mA, MarchingSquaresCollider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(PolygonCollider &a, glm::mat4 &mA, MarchingSquaresCollider &b, glm::mat4 &mB);
public:
	virtual int getClassID() = 0;
	virtual glm::vec4 boundingBox(glm::mat4 &transform) = 0;
	virtual ~Collider(){};

	static const int LOW_ITERATIONS, HIGH_ITERATIONS;
	static std::pair<double, double> intersection(Collider &a, glm::mat4 &mA, Collider &b, glm::mat4 &mB);
	static std::pair<double, double> intersection(Entity &a, Entity &b);
};
