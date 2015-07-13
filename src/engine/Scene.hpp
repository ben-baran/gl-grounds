#pragma once

#include "Entity.hpp"
#include <string>

class Scene
{
public:
	static Entity get(std::string name);
};