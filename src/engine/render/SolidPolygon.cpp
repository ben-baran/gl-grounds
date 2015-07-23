#include <src/engine/util/Res.hpp>
#include "SolidPolygon.hpp"

#include <src/engine/physics/RectangleCollider.hpp>

int SolidPolygon::attributes[] = {3, 3};

void SolidPolygon::constructVAO()
{

}

SolidPolygon::SolidPolygon(std::vector<std::pair<float, float>> &points, float r, float g, float b, double layer)
{
	Renderable::setLayer(layer);
	constructVAO();
	shader = Res::loadShader("res/shader/simple/color");
}

SolidPolygon::~SolidPolygon()
{
	delete vao;
}

void SolidPolygon::setLayer(double layer)
{
	Renderable::setLayer(layer);
}

void SolidPolygon::render()
{

}

void SolidPolygon::render(glm::mat4 transformMatrix)
{

}

Collider &SolidPolygon::provideCollider()
{
	return *(new RectangleCollider(0.0, 0.0, 0.0, 0.0));
}
