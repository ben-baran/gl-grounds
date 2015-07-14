#pragma once

#include <src/engine/render/Transform.hpp>
#include <src/engine/render/Renderable.hpp>
#include <src/engine/physics/Collider.hpp>

#include <unordered_set>
#include <string>

class Entity
{
friend class Scene;

private:
	double importance;

	std::unordered_set<std::string> tags;
	bool tagsChanged;

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

	const std::unordered_set<std::string> &getTags();
	bool hasTag(std::string tag);
	void addTag(std::string tag);
	void removeTag(std::string tag);

	Entity(Renderable *renderable, Transform *transform = new Transform());
	Entity(Renderable *renderable, Collider *collider, Transform *transform = new Transform());
};
