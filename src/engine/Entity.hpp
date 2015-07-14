#pragma once

#include <src/engine/render/Transform.hpp>
#include <src/engine/render/Renderable.hpp>
#include <src/engine/physics/Collider.hpp>

#include <string>

class Entity
{
private:
	double importance;

	Renderable *renderable;
	Collider *collider;
	Transform *transform;
public:
	double getImportance();
	void setImportance(double importance);
	void setImportanceBefore(std::initializer_list<std::string> names);
	void setImportanceBetween(std::string before, std::string after);
	void setImportanceAfter(std::initializer_list<std::string> names);

	Renderable &getRenderable();
	Collider &getCollider();
	Transform &getTransform();

	Entity(Renderable *renderable, Transform *transform = new Transform());
	Entity(Renderable *renderable, Collider *collider, Transform *transform = new Transform());
};
