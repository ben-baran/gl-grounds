#include "Scene.hpp"

using std::string;

Camera Scene::camera(0, 0, 1, 1);

std::map<std::string, Entity*, Entity::PointerCompare> Scene::entitiesByName;
std::unordered_map<std::string, Entity*> Scene::nameAddBuffer;
std::unordered_map<std::string, Entity*> Scene::nameRemoveBuffer;

std::unordered_map<std::string, std::unordered_set<Entity*>> Scene::entitiesByTag;
std::unordered_map<std::string, std::unordered_set<Entity*>> Scene::tagAddBuffer;
std::unordered_map<std::string, std::unordered_set<Entity*>> Scene::tagRemoveBuffer;

void Scene::addEntityToTag(Entity &entity, std::string tag)
{
	tagAddBuffer[tag].insert(&entity);
	tagRemoveBuffer[tag].erase(&entity);
}

void Scene::removeEntityFromTag(Entity &entity, std::string tag)
{
	tagRemoveBuffer[tag].insert(&entity);
	tagAddBuffer[tag].erase(&entity);
}

Camera &Scene::getCamera()
{
	return camera;
}

void Scene::add(Entity &entity, std::string name)
{
	nameAddBuffer[name] = &entity;
	nameRemoveBuffer.erase(name);
}

void Scene::remove(Entity &entity, std::string name)
{
	nameRemoveBuffer[name] = &entity;
	nameAddBuffer.erase(name);
}

Entity &Scene::get(string name)
{
	return *(entitiesByName[name]);
}

void Scene::update(double dt)
{
	for(auto &pair : entitiesByName) pair.second->update(dt);
}

void Scene::draw()
{
	for(auto &pair : entitiesByName) pair.second->draw();
}

void Scene::updateBuffers()
{
	for(auto &pair : nameAddBuffer) entitiesByName[pair.first] = pair.second;
	for(auto &pair : nameRemoveBuffer)
	{
		entitiesByName.erase(pair.first);
		delete pair.second;
	}

	for(auto &pair : tagAddBuffer) entitiesByTag[pair.first].insert(pair.second.begin(), pair.second.end());
	for(auto &pair : tagRemoveBuffer) entitiesByTag[pair.first].erase(pair.second.begin(), pair.second.end());
}
