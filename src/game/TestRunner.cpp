#include <src/engine/Entity.hpp>
#include <src/engine/render/SolidRectangle.hpp>
#include <src/engine/Scene.hpp>
#include <src/engine/util/KeyHandler.hpp>
#include <src/engine/util/MouseHandler.hpp>
#include <iostream>
#include <src/engine/render/SolidGrid.hpp>
#include <src/game/procedural/GridManip.hpp>
#include <src/engine/render/SolidPolygon.hpp>
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

void createLevel()
{
	Transform &transform = Scene::get("player").getTransform();
	Scene::remove("end");
	Scene::removeAll("wall");

	int sizeX = 50, sizeY = 50;
	vector<vector<bool>> map(sizeX, vector<bool>(sizeY));

	bool isUnified = false;
	while(!isUnified)
	{
		GridManip::fillRandom(map, 0.45);
		GridManip::cellularGenerate(map, {4, 5, 6, 7, 8}, {0, 5, 6, 7, 8}, 5);
		GridManip::cellularGenerate(map, {4, 5, 6, 7, 8}, {5, 6, 7, 8}, 5);
		GridManip::removeSingles(map);
		isUnified = GridManip::unifyRegions(map);
	}

	GridManip::surround(map, 10);
	Entity *grid = new Entity(new SolidGrid(map, map.size(), map[0].size(), 0, 0, 2, 2));
	grid->addTag("wall");
	Scene::add(*grid);

	auto pCoords = GridManip::emptyLoc(map);
	transform.setTranslation(pCoords.first * 2 + 0.5, pCoords.second * 2 + 0.5);

	auto eCoords = GridManip::emptyLocOtherQuadrant(map, pCoords);
	Entity *end = new Entity(new SolidRectangle(eCoords.first * 2 + 0.5, eCoords.second * 2 + 0.5, 1, 1, 0.9f, 0.5f, 0.6f));
	end->getRenderable().setLayerBelow({"player"});
	Scene::add("end", *end);
}

void TestRunner::setup()
{
	Entity *player = new Entity(new SolidRectangle(-0.5, -0.5, 1, 1, 0.5, 0.5, 0.9));
	Scene::add("player", *player);
//	createLevel();

	std::vector<std::pair<float, float>> points;
	points.push_back(std::make_pair(1.0f, 1.0f));
	points.push_back(std::make_pair(3.0f, 3.0f));
	points.push_back(std::make_pair(8.0f, 1.5f));
	points.push_back(std::make_pair(7.0f, 0.8f));
	Entity *poly = new Entity(new SolidPolygon(points));
	poly->addTag("wall");
	Scene::add(*poly);
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

	double speed = 0.16;
	if(KeyHandler::held(GLFW_KEY_LEFT_SHIFT) || KeyHandler::held(GLFW_KEY_RIGHT_SHIFT)) speed *= 2;
	if(KeyHandler::held(GLFW_KEY_W)) transform.translate(0, speed);
	if(KeyHandler::held(GLFW_KEY_A)) transform.translate(-speed, 0);
	if(KeyHandler::held(GLFW_KEY_S)) transform.translate(0, -speed);
	if(KeyHandler::held(GLFW_KEY_D)) transform.translate(speed, 0);

	if(KeyHandler::held(GLFW_KEY_R)) Scene::getCamera().getInverseTransform().scale(0.97, 0.97);
	if(KeyHandler::held(GLFW_KEY_F)) Scene::getCamera().getInverseTransform().scale(1.03, 1.03);

//	auto collision = Collider::intersection(Scene::get("player"), Scene::get("end"));
//	if(collision.first != 0 && collision.second != 0)
//	{
//		createLevel();
//	}

	Scene::get("player").collideByTag("wall");

	Scene::getCamera().getInverseTransform().setTranslation(transform.getDX(), transform.getDY());
}

void TestRunner::cleanup(){}
