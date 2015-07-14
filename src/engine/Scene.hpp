#pragma once

#include "Entity.hpp"

#include <unordered_map>
#include <unordered_set>
#include <string>

class Scene
{
private:
	static std::unordered_map<std::string, Entity*> entitiesByName;
	static std::unordered_map<std::string, Entity*> nameAddBuffer;
	static std::unordered_map<std::string, Entity*> nameRemoveBuffer;

	static std::unordered_map<std::string, std::unordered_set<Entity*>> entitiesByTag;
	static std::unordered_map<std::string, std::unordered_set<Entity*>> tagAddBuffer;
	static std::unordered_map<std::string, std::unordered_set<Entity*>> tagRemoveBuffer;

	static void addEntityToTag(Entity &entity, std::string tag);
	static void removeEntityFromTag(Entity &entity, std::string tag);

public:

	static void add(Entity &entity, std::string name);
	static void remove(Entity &entity, std::string name);
	static Entity &get(std::string name);
	static void update(double dt);
	static void draw();
	static void updateBuffers();

	friend void Entity::addTag(std::string tag);
	friend void Entity::removeTag(std::string tag);
};