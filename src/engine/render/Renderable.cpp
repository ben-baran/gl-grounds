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

double Renderable::layerBelow(std::initializer_list<std::string> names)
{
	double min = INFINITY;
	for(string name : names) min = std::min(min, Scene::get(name).getRenderable().getLayer());
	return (min - 1) / 2; //needed because bounds are -1 to 1 in depth buffer
}

double Renderable::layerBetween(std::string bottom, std::string top)
{
	return (Scene::get(bottom).getRenderable().getLayer() + Scene::get(top).getRenderable().getLayer()) / 2;
}

double Renderable::layerAbove(std::initializer_list<std::string> names)
{
	double max = -INFINITY;
	for(string name : names) max = std::max(max, Scene::get(name).getRenderable().getLayer());
	return (max + 1) / 2; //needed because bounds are -1 to 1 in depth buffer
}

double Renderable::layerBelowTag(std::string tag)
{
	double min = INFINITY;
	auto entities = Scene::getAll(tag);
	for(auto entity : entities) min = std::min(min, entity->getRenderable().getLayer());
	return (min - 1) / 2; //needed because bounds are -1 to 1 in depth buffer
}

double Renderable::layerAboveTag(std::string tag)
{
	double max = -INFINITY;
	auto entities = Scene::getAll(tag);
	for(auto entity : entities) max = std::max(max, entity->getRenderable().getLayer());
	return (max + 1) / 2; //needed because bounds are -1 to 1 in depth buffer
}

Renderable::~Renderable(){}

