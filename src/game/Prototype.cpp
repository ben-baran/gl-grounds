#include "Prototype.hpp"

using std::string;

Prototype::Prototype(string title): Prototype(title){}

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

	Entity weapon = new Entity(new SolidRectangle(1, 0.1));
	weapon.getTransform().translate(0.3, 0.3).rotate(glm::radians(-45)).attach(player.getTransform());
	weapon.bProperty("toggled") = false;
	weapon.setImportanceAfter({"player"});
	weapon.getRenderable().setLayerBelow({"player", "wall"});
	Scene::add("weapon", weapon);
}

void Prototype::update(double dt)
{
	Entity player = Scene::get("player");

	Transform &pTrans = player.getTransform();
	if(KeyHandler::held(GLFW_KEY_W)) pTrans.translate(0, -dt);
	if(KeyHandler::held(GLFW_KEY_A)) pTrans.translate(-dt, 0);
	if(KeyHandler::held(GLFW_KEY_S)) pTrans.translate(0, dt);
	if(KeyHandler::held(GLFW_KEY_D)) pTrans.translate(dt, 0);
	player.getTransform().setRotation(std::atan((MouseHandler.getWorldX() - pTrans.getTranslationX()) /
												(MouseHandler.getWorldY() - pTrans.getTranslationY())));
	player.collideByTags("wall");

	if(MouseHandler.clicked(GLFW_MOUSE_BUTTON_1))
	{
		Entity weapon = Scene::get("weapon");
		if(weapon.bProperty("toggled"))
		{
			weapon.getTransform().queueAnimation(0.3, Ease::cubicInOut)
												 .addComponent(glm::radians(90), Transform::ROTATE),
												 .addComponent(-0.6, Transform::TRANSLATE_Y));
		}
		else
		{
			weapon.getTransform().queueAnimation(0.3, Ease::cubicInOut)
												 .addComponent(glm::radians(90), Transform::ROTATE),
												 .addComponent(-0.6, Transform::TRANSLATE_Y));
		}
	}

	Scene::getCamera().getInverseTransform().setTranslation(player.getTransform());
}

void Prototype::cleanup(){}
