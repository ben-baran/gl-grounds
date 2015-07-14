#pragma once

#include <src/engine/render/Transform.hpp>
#include <src/engine/render/Renderable.hpp>
#include <src/engine/physics/Collider.hpp>

class Entity
{
private:
	Renderable *renderable;
	Collider *collider;
	Transform *transform;
public:
	Renderable &getRenderable();
	Collider &getCollider();
	Transform &getTransform();

	Entity(Renderable *renderable, Transform *transform = new Transform());
	Entity(Renderable *renderable, Collider *collider, Transform *transform = new Transform());
};
