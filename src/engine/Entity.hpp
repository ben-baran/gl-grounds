#pragma once

#include <src/engine/anim/Transform.hpp>
#include <src/engine/render/Renderable.hpp>
#include <src/engine/physics/Collider.hpp>

#include <unordered_set>
#include <unordered_map>
#include <string>

class Entity
{
private:
	double importance;

	std::unordered_set<std::string> tags;
	std::unordered_map<std::string, void *> properties;

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

    template <class T> T& get(std::string name) {
        return *((T*) properties[name]);
    }

    template <class T> void set(std::string name, T t) {
        properties[name] = &t;
    }

    template <class T> void setPointer(std::string name, T *t) {
        properties[name] = t;
    }

	Entity(Renderable *renderable, Transform *transform = new Transform());
	Entity(Renderable *renderable, Collider *collider, Transform *transform = new Transform());

	virtual void update(double dt);
	void draw();

	struct PairCompare
	{
		bool operator()(const std::pair<std::string, Entity*> &left, const std::pair<std::string, Entity*> &right) const;
	};
	static PairCompare pairCompare;

	~Entity();

	void collideByName(std::string name);
	void collideByTag(std::string tag, int iterations = Collider::LOW_ITERATIONS);
};
