#include "Renderable.hpp"

#include <src/engine/Scene.hpp>

using std::string;

double Renderable::getLayer()
{
	return layer;
}

void Renderable::setLayer(int layer)
{
	this->layer = layer;
}

void Renderable::setLayerBelow(std::initializer_list<std::string> names)
{
	double min = INFINITY;
	for(string name : names) min = std::min(min, Scene::get(name).getRenderable().getLayer());
	layer = min - 1;
}

void Renderable::setLayerBetween(std::string bottom, std::string top)
{
	layer = (Scene::get(bottom).getRenderable().getLayer() + Scene::get(top).getRenderable().getLayer()) / 2;
}

void Renderable::setLayerAbove(std::initializer_list<std::string> names)
{
	double max = -INFINITY;
	for(string name : names) max = std::max(max, Scene::get(name).getRenderable().getLayer());
	layer = max + 1;
}
