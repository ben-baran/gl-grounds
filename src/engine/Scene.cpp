#include "Scene.hpp"

#include <vector>
#include <string>

using std::string;

Camera Scene::camera(0, 0, 1, 1);

std::unordered_map<std::string, Entity*> Scene::entitiesByName;
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

void Scene::add(std::string name, Entity &entity)
{
	nameAddBuffer[name] = &entity;
	nameRemoveBuffer.erase(name);
}

void Scene::add(Entity &entity)
{
	add(std::to_string(((long) &entity)), entity);
}

void Scene::remove(std::string name, Entity &entity)
{
	nameRemoveBuffer[name] = &entity;
	nameAddBuffer.erase(name);
}

Entity &Scene::get(string name)
{
	auto find = entitiesByName.find(name);
	if(find != entitiesByName.end()) return *(find->second);
	return *(nameAddBuffer[name]);
}

void Scene::update(double dt)
{
	std::vector<std::pair<string, Entity*>> entityVector(entitiesByName.begin(), entitiesByName.end());
	sort(entityVector.begin(), entityVector.end(), Entity::pairCompare);
	for(auto &pair : entityVector) pair.second->update(dt);
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
