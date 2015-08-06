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

	std::string name;

	std::unordered_set<std::string> tags;
	std::unordered_map<std::string, bool> bProperties;
	std::unordered_map<std::string, int> iProperties;
	std::unordered_map<std::string, float> fProperties;
	std::unordered_map<std::string, double> dProperties;
	std::unordered_map<std::string, std::string> sProperties;
	std::unordered_map<std::string, Entity*> eProperties;

	Renderable *renderable;
	Collider *collider;
	Transform *transform;
public:
	double getImportance() const;
	void setImportance(double importance);
	void setImportanceBefore(std::initializer_list<std::string> names);
	void setImportanceBetween(std::string before, std::string after);
	void setImportanceAfter(std::initializer_list<std::string> names);

	std::string getName();
	void setName(std::string &name);

	Renderable &getRenderable();
	Collider &getCollider();
	Transform &getTransform();

	const std::unordered_set<std::string> &getTags();
	bool hasTag(std::string tag);
	void addTag(std::string tag);
	void removeTag(std::string tag);

	bool &bProperty(std::string name);
	int &iProperty(std::string name);
	float &fProperty(std::string name);
	double &dProperty(std::string name);
	std::string &sProperty(std::string name);
	Entity *&eProperty(std::string name);

	Entity(Renderable *renderable, Transform *transform = new Transform());
	Entity(Renderable *renderable, Collider *collider, Transform *transform = new Transform());

	virtual void update(double dt);
	virtual void draw();

	struct PairCompare
	{
		bool operator()(const std::pair<std::string, Entity*> &left, const std::pair<std::string, Entity*> &right) const;
	};
	static PairCompare pairCompare;

	~Entity();

	void collideByName(std::string name);
	void collideByTag(std::string tag, int iterations = Collider::LOW_ITERATIONS);
};
