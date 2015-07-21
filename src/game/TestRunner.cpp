#include <src/engine/Entity.hpp>
#include <src/engine/render/SolidRectangle.hpp>
#include <src/engine/Scene.hpp>
#include <src/engine/util/KeyHandler.hpp>
#include <src/engine/util/MouseHandler.hpp>
#include <iostream>
#include <src/game/procedural/CellularAutomata.hpp>
#include <src/engine/render/SolidGrid.hpp>
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
//	int emptyX = 0, emptyY = 0;
//	int sizeX = 10, sizeY = 10;
//	vector<vector<bool>> map(sizeX, vector<bool>(sizeY));
//	CellularAutomata::generateWithRules(map, sizeX, sizeY, {3, 4, 5, 6, 7, 8}, {6, 7, 8}, 4, 0.5);
//
//	for(int i = 0; i < sizeX; i++) for(int j = 0; j < sizeY; j++)
//	{
//		if(map[i][j]) placeWall(i * 2, j * 2);
//	}
	Entity *player = new Entity(new SolidRectangle(-0.5, -0.5, 1, 1, 0.5, 0.5, 0.9));
//	player->getTransform().setTranslation(emptyX, emptyY);
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

	double speed = 0.8;
	if(KeyHandler::held(GLFW_KEY_LEFT_SHIFT) || KeyHandler::held(GLFW_KEY_RIGHT_SHIFT)) speed *= 2;
	if(KeyHandler::held(GLFW_KEY_W)) transform.translate(0, speed);
	if(KeyHandler::held(GLFW_KEY_A)) transform.translate(-speed, 0);
	if(KeyHandler::held(GLFW_KEY_S)) transform.translate(0, -speed);
	if(KeyHandler::held(GLFW_KEY_D)) transform.translate(speed, 0);

	if(KeyHandler::pressed(GLFW_KEY_SPACE))
	{
//		Scene::removeAll("wall");
		int sizeX = 100, sizeY = 100;
		vector<vector<bool>> map(sizeX, vector<bool>(sizeY));
		CellularAutomata::generateWithRules(map, sizeX, sizeY, {3, 4, 5, 6, 7, 8}, {6, 7, 8}, 4, 0.5);

		Entity *grid = new Entity(new SolidGrid(map, sizeX, sizeY, transform.getDX(), transform.getDY(), 2, 2));
		Scene::add(*grid);
//		for(int i = 0; i < sizeX; i++) for(int j = 0; j < sizeY; j++) if(map[i][j]) placeWall(transform.getDX() + i * 2,
//																							  transform.getDY() + j * 2);
	}

	Scene::get("player").collideByTag("wall");

	Scene::getCamera().getInverseTransform().setTranslation(transform.getDX(), transform.getDY());
}

void TestRunner::cleanup(){}
