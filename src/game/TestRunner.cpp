#include <src/engine/Entity.hpp>
#include <src/engine/render/SolidRectangle.hpp>
#include <src/engine/Scene.hpp>
#include "TestRunner.hpp"

int main()
{
	Run::start(new TestRunner());
}

void TestRunner::setup()
{
	Entity *player = new Entity(new SolidRectangle(-0.25, -0.25, 0.5, 0.5, 0.5, 0.5, 0.9));
	Scene::add("player", *player);

	Entity *secondary = new Entity(new SolidRectangle(-0.1, -0.1, 0.2, 0.2, 0.9, 0.5, 0.5));
	Scene::add("secondary", *secondary);
	secondary->getRenderable().setLayerAbove({"player"});
}

void TestRunner::update(double dt)
{

}

void TestRunner::cleanup(){}
