#pragma once

#include <src/engine/Entity.hpp>

//UI Component
class UIC: public Entity
{

public:
	UIC(Renderable *renderable, Transform *transform) : Entity(renderable, transform)
	{ }
};
