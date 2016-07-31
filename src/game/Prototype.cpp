#include <src/engine/Entity.hpp>
#include <src/engine/render/SolidRectangle.hpp>
#include <src/engine/Scene.hpp>
#include <src/engine/util/KeyHandler.hpp>
#include <src/engine/util/MouseHandler.hpp>
#include <src/engine/anim/Ease.hpp>
#include <iostream>
#include "Prototype.hpp"

using std::string;

int main()
{
	Run::start(new Prototype());
}

void Prototype::setup()
{
	Entity *player = new Entity(new SolidRectangle(-0.5, -0.5, 1, 1));
	Entity *wall0 = new Entity(new SolidRectangle(-2, -2, 1, 1));
	wall0->addTag("wall");
	Entity *wall1 = new Entity(new SolidRectangle(2, 3, 2, 0.5));
	wall1->addTag("wall");

	Scene::add("player", *player);
	Scene::add(*wall0);
	Scene::add(*wall1);

	Entity *weapon = new Entity(new SolidRectangle(1, 0.1));
	weapon->getTransform().translate(0.3, 0.3).rotate(glm::radians(-45.0f)).attach(&(player->getTransform()));
	weapon->set("toggled", false);
	weapon->setImportanceAfter({"player"});
	weapon->getRenderable().setLayerBelow({"player"});
	weapon->getRenderable().setLayerBelowTag("wall");
	Scene::add("weapon", *weapon);
}

void Prototype::update(double dt)
{
	Entity &player = Scene::get("player");

	Transform &pTrans = player.getTransform();
	double speed = 5.0;
	if(KeyHandler::held(GLFW_KEY_W)) pTrans.translate(0, dt * speed);
	if(KeyHandler::held(GLFW_KEY_A)) pTrans.translate(-dt * speed, 0);
	if(KeyHandler::held(GLFW_KEY_S)) pTrans.translate(0, -dt * speed);
	if(KeyHandler::held(GLFW_KEY_D)) pTrans.translate(dt * speed, 0);

	auto worldCoords = MouseHandler::getWorldCoords();
	player.getTransform().setRotation(-std::atan((worldCoords.first - pTrans.getDX()) / (worldCoords.second - pTrans.getDY())));
	player.collideByTag("wall");

	if(MouseHandler::pressed(GLFW_MOUSE_BUTTON_1))
	{
		Entity &weapon = Scene::get("weapon");
		if(weapon.get<bool>("toggled"))
		{
			std::cout << "Untoggled" << std::endl;
			weapon.getTransform().queueAnimation(0.3, Ease::cubicInOut)
					.addComponent(glm::radians(90.0f), &Transform::rotate)
					.addComponent(-0.6, &Transform::translateY);
			weapon.set("toggled", false);
		}
		else
		{
			std::cout << "Toggled" << std::endl;
			weapon.getTransform().queueAnimation(0.3, Ease::cubicInOut)
					.addComponent(glm::radians(90.0f), &Transform::rotate)
					.addComponent(-0.6, &Transform::translateY);
			weapon.set("toggled", true);
		}
	}

	Scene::getCamera().getInverseTransform().setTranslation(pTrans.getDX(), pTrans.getDY());
}

void Prototype::cleanup(){}
