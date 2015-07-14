#pragma once

#include <src/engine/physics/Collider.hpp>
#include <string>
#include "Transform.hpp"

class Renderable
{
private:
	double layer;
public:
	double getLayer();
	void setLayer(int layer);
	void setLayerBelow(std::initializer_list<std::string> names);
	void setLayerBetween(std::string bottom, std::string top);
	void setLayerAbove(std::initializer_list<std::string> names);

	virtual void render() = 0;
	virtual void render(Transform transform) = 0;
	virtual Collider &provideCollider() = 0;
};