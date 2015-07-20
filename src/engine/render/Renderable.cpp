#include "Renderable.hpp"

#include <src/engine/Scene.hpp>

using std::string;

double Renderable::getLayer()
{
	return layer;
}

void Renderable::setLayer(double layer)
{
	this->layer = -layer; //negative because of GL_LESS parameter in glDepthFunc
}

void Renderable::setLayerBelow(std::initializer_list<std::string> names)
{
	double min = INFINITY;
	for(string name : names) min = std::min(min, Scene::get(name).getRenderable().getLayer());
	setLayer((min - 1) / 2); //needed because bounds are -1 to 1 in depth buffer
}

void Renderable::setLayerBetween(std::string bottom, std::string top)
{
	setLayer((Scene::get(bottom).getRenderable().getLayer() + Scene::get(top).getRenderable().getLayer()) / 2);
}

void Renderable::setLayerAbove(std::initializer_list<std::string> names)
{
	double max = -INFINITY;
	for(string name : names) max = std::max(max, Scene::get(name).getRenderable().getLayer());
	setLayer((max + 1) / 2); //needed because bounds are -1 to 1 in depth buffer
}

void Renderable::setLayerBelowTag(std::string tag)
{
	double min = INFINITY;
	auto entities = Scene::getAll(tag);
	for(auto entity : entities) min = std::min(min, entity->getRenderable().getLayer());
	setLayer((min - 1) / 2); //needed because bounds are -1 to 1 in depth buffer
}

void Renderable::setLayerAboveTag(std::string tag)
{
	double max = -INFINITY;
	auto entities = Scene::getAll(tag);
	for(auto entity : entities) max = std::max(max, entity->getRenderable().getLayer());
	setLayer((max + 1) / 2); //needed because bounds are -1 to 1 in depth buffer
}

Renderable::~Renderable(){}

