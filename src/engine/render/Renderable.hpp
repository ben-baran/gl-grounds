#pragma once

#include <src/engine/physics/Collider.hpp>
#include <string>
#include <src/engine/anim/Transform.hpp>

class Renderable
{
private:
	double layer;
public:
	double getLayer();
	virtual void setLayer(double layer);
	void setLayerBelow(std::initializer_list<std::string> names);
	void setLayerBetween(std::string bottom, std::string top);
	void setLayerAbove(std::initializer_list<std::string> names);

	virtual void render() = 0;
	virtual void render(glm::mat4 transformMatrix) = 0;
	virtual Collider &provideCollider() = 0;

	virtual ~Renderable() = 0;
};