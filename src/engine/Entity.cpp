#include "Entity.hpp"
#include "Scene.hpp"

using std::string

double Entity::importance = 0;

Renderable *Entity::renderable;
Collider *Entity::collider;
Transform *Entity::transform;

double Entity::getImportance()
{
	return importance;
}

void Entity::setImportance(double importance)
{
	this->importance = importance;
}

void Entity::setImportanceBefore(std::initializer_list<string> names)
{
	double min = INFINITY;
	for(string name : names) min = std::min(min, Scene::get(name).getImportance());
	importance = min - 1;
}

void Entity::setImportanceBetween(string before, string after)
{
	importance = (Scene::get(before).getImportance() + Scene::get(after).getImportance()) / 2;
}

void Entity::setImportanceAfter(std::initializer_list<string> names)
{
	double max = -INFINITY;
	for(string name : names) max = std::max(max, Scene::get(name).getImportance());
	importance = max + 1;
}

Renderable &Entity::getRenderable()
{
	return *renderable;
}

Collider &Entity::getCollider()
{
	return *collider;
}

Transform &Entity::getTransform()
{
	return *transform;
}

Entity::Entity(Renderable *renderable, Transform *transform)
{
	this->renderable = renderable;
	this->collider = new Collider(renderable->provideCollider());
	this->transform = transform;
}

Entity::Entity(Renderable *renderable, Collider *collider, Transform *transform)
{
	this->renderable = renderable;
	this->collider = collider;
	this->transform = transform;
}
