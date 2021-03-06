#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "Entity.hpp"
#include <src/engine/render/Camera.hpp>

class Scene
{
private:
	static Camera camera;

	static std::unordered_map<std::string, Entity*> entitiesByName;
	static std::unordered_map<std::string, Entity*> nameAddBuffer;
	static std::unordered_map<std::string, Entity*> nameRemoveBuffer;

	static std::unordered_map<std::string, std::unordered_set<Entity*>> entitiesByTag;
	static std::unordered_map<std::string, std::unordered_set<Entity*>> tagAddBuffer;
	static std::unordered_map<std::string, std::unordered_set<Entity*>> tagRemoveBuffer;

	static std::unordered_map<std::string, Entity*> uiEntities;
	static std::unordered_map<std::string, Entity*> uiAddBuffer;
	static std::unordered_map<std::string, Entity*> uiRemoveBuffer;

	static void addEntityToTag(Entity &entity, std::string tag);
	static void removeEntityFromTag(Entity &entity, std::string tag);

public:
	static Camera &getCamera();

	static void add(std::string name, Entity &entity);
	static void add(Entity &entity);
	static void remove(std::string name);
	static void removeAll(std::string tag);
	static Entity &get(std::string name);
	static std::unordered_set<Entity*> &getAll(std::string tag);
	static void update(double dt);
	static void draw();
	static void updateBuffers();

	friend void Entity::addTag(std::string tag);
	friend void Entity::removeTag(std::string tag);

	static Entity &getUI(std::string name);
	static void addUI(std::string name, Entity &entity);
	static void removeUI(std::string name);
};