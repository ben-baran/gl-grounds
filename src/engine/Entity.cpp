#include <string>
#include <memory>
#include "Entity.hpp"

#include "Entity.hpp"

#include "Scene.hpp"

using std::string;

double Entity::getImportance() const {
	return importance;
}

void Entity::setImportance(double importance) {
	this->importance = importance;
}

void Entity::setImportanceBefore(std::initializer_list<string> names) {
	double min = INFINITY;
	for(string name : names) min = std::min(min, Scene::get(name).getImportance());
	importance = min - 1;
}

void Entity::setImportanceBetween(string before, string after) {
	importance = (Scene::get(before).getImportance() + Scene::get(after).getImportance()) / 2;
}

void Entity::setImportanceAfter(std::initializer_list<string> names) {
	double max = -INFINITY;
	for(string name : names) max = std::max(max, Scene::get(name).getImportance());
	importance = max + 1;
}

string Entity::getName()
{
	return name;
}

void Entity::setName(std::string &name)
{
	this->name = name;
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

const std::unordered_set<std::string> &Entity::getTags()
	return *renderable;
}

Collider &Entity::getCollider() {
	return *collider;
}

Transform &Entity::getTransform() {
	return *transform;
}

const std::unordered_set<std::string> &Entity::getTags() {
	return tags;
}

bool Entity::hasTag(std::string tag) {
	return tags.find(tag) != tags.end();
}

void Entity::addTag(std::string tag) {
	Scene::addEntityToTag(*this, tag);
	tags.insert(tag);
}

void Entity::removeTag(std::string tag) {
	Scene::removeEntityFromTag(*this, tag);
	tags.erase(tag);
}

Entity::Entity(Renderable *renderable, Transform *transform) {
	this->renderable = renderable;
	this->collider = &(renderable->provideCollider());
	this->transform = transform;
}

Entity::Entity(Renderable *renderable, Collider *collider, Transform *transform) {
	this->renderable = renderable;
	this->collider = collider;
	this->transform = transform;
}

void Entity::update(double dt) {}

void Entity::draw() {
	renderable->render((glm::mat4) (Scene::getCamera().getTransformMatrix()) * transform->getMatrix());
}

Entity::~Entity() {
	delete renderable;
	delete collider;
	delete transform;
}

bool Entity::PairCompare::operator()(const std::pair<std::string, Entity *> &left,
									 const std::pair<std::string, Entity *> &right) const {
	return left.second->getImportance() < right.second->getImportance();
}

void Entity::collideByName(std::string name) {
	Entity other = Scene::get(name);
	auto coords = Collider::intersection(*collider, *transform, other.getCollider(), other.getTransform());

	transform->translate(coords.first, coords.second);
}

void Entity::collideByTag(std::string tag, int iterations) {
	auto entities = Scene::getAll(tag);
	for(int i = 0; i < iterations; i++) for(auto entity : entities) if(entity != this)
	{
		auto coords = Collider::intersection(*collider, transform->getMatrix(),
											 entity->getCollider(), entity->getTransform().getMatrix());
		transform->translate(coords.first, coords.second);
	}
}
