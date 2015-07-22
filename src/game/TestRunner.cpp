#include <src/engine/Entity.hpp>
#include <src/engine/render/SolidRectangle.hpp>
#include <src/engine/Scene.hpp>
#include <src/engine/util/KeyHandler.hpp>
#include <src/engine/util/MouseHandler.hpp>
#include <iostream>
#include <src/engine/render/SolidGrid.hpp>
#include <src/game/procedural/GridManip.hpp>
#include "TestRunner.hpp"

using std::vector;

int main()
{
	Run::start(new TestRunner());
}

void placeWall(int x, int y)
{
	Entity *wall = new Entity(new SolidRectangle(x, y, 2, 2));
	wall->addTag("wall");
	Scene::add(*wall);
}

void TestRunner::setup()
{
	Entity *player = new Entity(new SolidRectangle(-0.5, -0.5, 1, 1, 0.5, 0.5, 0.9));
	Scene::add("player", *player);
}

void TestRunner::update(double dt)
{
	if(KeyHandler::pressed(GLFW_KEY_ESCAPE)) end();

	Transform &transform = Scene::get("player").getTransform();

	auto coords = MouseHandler::getWorldCoords();
	if(MouseHandler::pressed(GLFW_MOUSE_BUTTON_1))
	{
		std::cout << coords.first << " " << coords.second << std::endl;
		std::cout << transform.getDX() << " " << transform.getDY() << std::endl;
		//transform.queueAnimation(1.0, Ease::backInOut).addComponent(1, &Transform::translateX);
	}
	transform.setRotation(std::atan2(coords.second - transform.getDY(), coords.first - transform.getDX()));

	double speed = 0.15;
	if(KeyHandler::held(GLFW_KEY_LEFT_SHIFT) || KeyHandler::held(GLFW_KEY_RIGHT_SHIFT)) speed *= 2;
	if(KeyHandler::held(GLFW_KEY_W)) transform.translate(0, speed);
	if(KeyHandler::held(GLFW_KEY_A)) transform.translate(-speed, 0);
	if(KeyHandler::held(GLFW_KEY_S)) transform.translate(0, -speed);
	if(KeyHandler::held(GLFW_KEY_D)) transform.translate(speed, 0);

	if(KeyHandler::held(GLFW_KEY_R)) Scene::getCamera().getInverseTransform().scale(0.97, 0.97);
	if(KeyHandler::held(GLFW_KEY_F)) Scene::getCamera().getInverseTransform().scale(1.03, 1.03);

	if(KeyHandler::pressed(GLFW_KEY_SPACE))
	{
//		Scene::removeAll("wall");

		for(int i = 0; i < 1; i++)
		{
			int sizeX = 100, sizeY = 100;
			vector<vector<bool>> map(sizeX, vector<bool>(sizeY));
			GridManip::fillRandom(map, 0.49);
			GridManip::cellularGenerate(map, {4, 5, 6, 7, 8}, {5, 6, 7, 8}, 5);
			GridManip::removeSingles(map);
			GridManip::surround(map, 10);

			Entity *grid = new Entity(new SolidGrid(map, map.size(), map[0].size(),
													200 * i + transform.getDX() - 100, transform.getDY() - 100, 2, 2));
			grid->addTag("wall");
			Scene::add(*grid);
		}
	}

	Scene::get("player").collideByTag("wall");

	Scene::getCamera().getInverseTransform().setTranslation(transform.getDX(), transform.getDY());
}

void TestRunner::cleanup(){}
