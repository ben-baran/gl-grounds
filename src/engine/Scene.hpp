#pragma once

#include "Entity.hpp"

#include <unordered_map>
#include <unordered_set>
#include <string>

class Scene
{
private:
	std::unordered_map<std::string, Entity*> entitiesByName;
	std::unordered_map<std::string, std::unordered_set<Entity*>> entitiesByTag;

	friend Entity void addEntityToTag(Entity entity, std::string tag);
	friend Entity void removeEntityFromTag(Entity entity, std::string tag);
public:
	static Entity get(std::string name);
};