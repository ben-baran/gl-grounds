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

std::unordered_map<std::string, Entity*> Scene::uiEntities;
std::unordered_map<std::string, Entity*> Scene::uiAddBuffer;
std::unordered_map<std::string, Entity*> Scene::uiRemoveBuffer;

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
	entity.setName(name);
	nameAddBuffer[name] = &entity;
	nameRemoveBuffer.erase(name);
}

void Scene::add(Entity &entity)
{
	add(std::to_string(((long) &entity)), entity);
}

void Scene::remove(std::string name)
{
	Entity *entity = &get(name);
	if(entity)
	{
		nameRemoveBuffer[name] = entity;
		nameAddBuffer.erase(name);
		for(const auto &tag : entity->getTags()) removeEntityFromTag(*entity, tag);
	}
}

void Scene::removeAll(std::string tag)
{
	for(auto entity : getAll(tag)) remove(entity->getName());
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

	std::vector<std::pair<string, Entity*>> uiVector(uiEntities.begin(), uiEntities.end());
	sort(uiVector.begin(), uiVector.end(), Entity::pairCompare);
	for(auto &pair : uiVector) pair.second->update(dt);
}

void Scene::draw()
{
	for(auto &pair : entitiesByName) pair.second->draw();
	for(auto &pair : uiEntities) pair.second->draw();
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
	for(auto &pair : tagRemoveBuffer)
	{
		for(Entity *entity : pair.second) entitiesByTag[pair.first].erase(entity);
	}

	for(auto &pair : uiAddBuffer) uiEntities[pair.first] = pair.second;
	for(auto &pair : uiRemoveBuffer)
	{
		uiEntities.erase(pair.first);
		delete pair.second;
	}

	nameAddBuffer.clear();
	nameRemoveBuffer.clear();
	tagAddBuffer.clear();
	tagRemoveBuffer.clear();
	uiAddBuffer.clear();
	uiRemoveBuffer.clear();
}

std::unordered_set<Entity*> &Scene::getAll(std::string tag)
{
	return entitiesByTag[tag];
}

Entity &Scene::getUI(std::string name)
{
	auto find = uiEntities.find(name);
	if(find != uiEntities.end()) return *(find->second);
	return *(uiAddBuffer[name]);
}

void Scene::addUI(std::string name, Entity &entity)
{
	entity.setName(name);
	uiAddBuffer[name] = &entity;
	uiRemoveBuffer.erase(name);
}

void Scene::removeUI(std::string name)
{
	Entity *entity = &getUI(name);
	if(entity)
	{
		uiRemoveBuffer[name] = entity;
		uiAddBuffer.erase(name);
	}
}
