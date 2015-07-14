#pragma once

#include <src/engine/render/Transform.hpp>
#include <src/engine/render/Renderable.hpp>
#include <src/engine/physics/Collider.hpp>

#include <unordered_set>
#include <string>
#include "Scene.hpp"

class Entity
{
private:
	double importance;

	std::unordered_set<std::string> tags;

	Renderable *renderable;
	Collider *collider;
	Transform *transform;
public:
	double getImportance() const;
	void setImportance(double importance);
	void setImportanceBefore(std::initializer_list<std::string> names);
	void setImportanceBetween(std::string before, std::string after);
	void setImportanceAfter(std::initializer_list<std::string> names);

	Renderable &getRenderable();
	Collider &getCollider();
	Transform &getTransform();

	const std::unordered_set<std::string> &getTags();
	bool hasTag(std::string tag);
	void addTag(std::string tag);
	void removeTag(std::string tag);

	Entity(Renderable *renderable, Transform *transform = new Transform());
	Entity(Renderable *renderable, Collider *collider, Transform *transform = new Transform());

	virtual void update(double dt);
	void draw();

	struct PointerCompare
	{
		bool operator()(const Entity *left, const Entity *right) const;
	};
};
