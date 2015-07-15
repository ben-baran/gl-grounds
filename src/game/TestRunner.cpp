#include <src/engine/Entity.hpp>
#include <src/engine/render/SolidRectangle.hpp>
#include <src/engine/Scene.hpp>
#include <src/engine/util/KeyHandler.hpp>
#include <src/engine/util/Window.hpp>
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
	secondary->getRenderable().setLayerBelow({"player"});
	secondary->getTransform().translate(0.5, 0).attach(&(player->getTransform()));
}

void TestRunner::update(double dt)
{
	if(KeyHandler::pressed(GLFW_KEY_ESCAPE)) end();
	Scene::get("player").getTransform().rotate(0.01);
	Scene::get("secondary").getTransform().rotate(-0.01);

	Transform &transform = Scene::get("player").getTransform();
	if(KeyHandler::held(GLFW_KEY_W)) transform.translate(0, 0.04);
	if(KeyHandler::held(GLFW_KEY_A)) transform.translate(-0.04, 0);
	if(KeyHandler::held(GLFW_KEY_S)) transform.translate(0, -0.04);
	if(KeyHandler::held(GLFW_KEY_D)) transform.translate(0.04, 0);
}

void TestRunner::cleanup(){}
