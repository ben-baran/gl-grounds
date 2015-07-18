#include <src/engine/Entity.hpp>
#include <src/engine/render/SolidRectangle.hpp>
#include <src/engine/Scene.hpp>
#include <src/engine/util/KeyHandler.hpp>
#include <src/engine/util/MouseHandler.hpp>
#include <iostream>
#include <src/engine/anim/Ease.hpp>
#include "TestRunner.hpp"

int main()
{
	Run::start(new TestRunner());
}

void TestRunner::setup()
{
	Entity *player = new Entity(new SolidRectangle(-0.5, -0.5, 1, 1, 0.5, 0.5, 0.9));
	Scene::add("player", *player);

	Entity *secondary = new Entity(new SolidRectangle(-0.4, -0.4, 0.8, 0.8, 0.9, 0.5, 0.5));
	Scene::add("secondary", *secondary);
	secondary->getRenderable().setLayerAbove({"player"});
	secondary->getTransform().translate(0.5, 0).attach(&(player->getTransform()));

	Entity *pointer = new Entity(new SolidRectangle(-0.01, -0.01, 0.02, 0.02, 0, 0, 0));
	Scene::add(*pointer);
	pointer->getRenderable().setLayerAbove({"player"});
	pointer->getTransform().attach(&(player->getTransform()));

	Entity &last = *secondary;
	for(int i = 1; i < 8; i++)
	{
		Entity *attached = new Entity(new SolidRectangle(-0.4 / (i + 1), -0.4 / (i + 1), 0.8 / (i + 1), 0.8 / (i + 1),
														 i / 15.0, i / 10.0, i / 15.0));
		attached->addTag("rotate");
		Scene::add(*attached);
		attached->getRenderable().setLayerBelow({"player"});
		attached->getTransform().translate(0.9 * i, 0).attach(&(last.getTransform()));
		last = *attached;
	}
}

void TestRunner::update(double dt)
{
	if(KeyHandler::pressed(GLFW_KEY_ESCAPE)) end();

	Transform &transform = Scene::get("player").getTransform();

	auto coords = MouseHandler::getWorldCoords();
	if(MouseHandler::pressed(GLFW_MOUSE_BUTTON_1))
	{
		transform.queueAnimation(0.7, Ease::quadraticInOut).addComponent(1, &Transform::translateX);
	}
	transform.setRotation(std::atan2(coords.second - transform.getDY(), coords.first - transform.getDX()));

	Scene::get("secondary").getTransform().rotate(0.01);
	for(auto &rotator : Scene::getAll("rotate")) rotator->getTransform().rotate(0.01);

	if(KeyHandler::held(GLFW_KEY_W)) transform.translate(0, 0.07);
	if(KeyHandler::held(GLFW_KEY_A)) transform.translate(-0.07, 0);
	if(KeyHandler::held(GLFW_KEY_S)) transform.translate(0, -0.07);
	if(KeyHandler::held(GLFW_KEY_D)) transform.translate(0.07, 0);
}

void TestRunner::cleanup(){}
