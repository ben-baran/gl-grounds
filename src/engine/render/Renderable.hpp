#pragma once

#include <src/engine/physics/Collider.hpp>
#include <string>
#include <src/engine/anim/Transform.hpp>

class Renderable
{
private:
	double layer = 0;
public:
	double getLayer();
	virtual void setLayer(double layer);
	static double layerBelow(std::initializer_list<std::string> names);
	static double layerBetween(std::string bottom, std::string top);
	static double layerAbove(std::initializer_list<std::string> names);
	static double layerBelowTag(std::string tag);
	static double layerAboveTag(std::string tag);

	virtual void render() = 0;
	virtual void render(glm::mat4 transformMatrix) = 0;
	virtual Collider &provideCollider() = 0;

	virtual ~Renderable() = 0;
};