#include <src/engine/Entity.hpp>
#include <src/engine/render/SolidRectangle.hpp>
#include <src/engine/Scene.hpp>
#include <src/engine/util/KeyHandler.hpp>
#include <src/engine/util/MouseHandler.hpp>
#include <iostream>
#include <src/engine/render/SolidGrid.hpp>
#include <src/game/procedural/GridManip.hpp>
#include <src/engine/render/SolidPolygon.hpp>
#include <src/engine/render/SolidMarchingSquares.hpp>
#include <src/engine/render/TexturedRectangle.hpp>
#include <src/engine/render/TextRenderable.hpp>
#include <src/game/procedural/GridWalk.hpp>
#include <src/engine/anim/Ease.hpp>
#include "TestRunner.hpp"

using std::vector;

int main()
{
	Run::start(new TestRunner());
}

void createLevel()
{
	Transform &transform = Scene::get("player").getTransform();
	Scene::remove("end");
	Scene::removeAll("wall");
	Scene::removeAll("text");

	int sizeX = 30, sizeY = 30;
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
//	Entity *grid = new Entity(new SolidGrid(map, map.size(), map[0].size(), 0, 0, 2, 2));
	SolidMarchingSquares *sms = new SolidMarchingSquares(map, map.size(), map[0].size(), 0, 0, 2, 2,
														 Renderable::layerBelow({"player"}));
	Entity *grid = new Entity(sms);
	grid->addTag("wall");
	Scene::add("grid", *grid);

	auto pCoords = GridManip::emptyLoc(sms->getMap());
//	auto pCoords = GridManip::emptyLoc(map);
	transform.setTranslation(pCoords.first * 2 + 0.5, pCoords.second * 2 + 0.5);

	auto eCoords = GridManip::emptyLocOtherQuadrant(sms->getMap(), pCoords);
//	auto eCoords = GridManip::emptyLocOtherQuadrant(map, pCoords);
	Entity *end = new Entity(new SolidRectangle(eCoords.first * 2 + 0.5, eCoords.second * 2 + 0.5, 1, 1, 0.9f, 0.5f, 0.6f,
												Renderable::layerBelow({"player"})));
	Scene::add("end", *end);

	vector<vector<int>> dMap(sizeX + 20, vector<int>(sizeY + 20, 0));
	GridWalk::generateDistanceField(sms->getMap(), dMap, pCoords.first, pCoords.second);
	vector<vector<int>> regions(sizeX + 20, vector<int>(sizeY + 20, 0));
	vector<vector<std::pair<int, int>>> regionList;
	GridWalk::createRegions(dMap, regions, regionList);

	for(int i = 0; i < sizeX + 20; i++)
	{
		for(int j = 0; j < sizeY + 20; j++) if(dMap[i][j] != -1)
		{
			Entity *text = new Entity(new TextRenderable(i * 2 + 0.5, j * 2 + 0.5, 0.5, 1,
														 std::to_string(regions[i][j]), 0.99));
			text->addTag("text");
			Scene::add(*text);
		}
	}
}

void TestRunner::setup()
{
	Entity *player = new Entity(new TexturedRectangle(-0.5, -0.5, 1, 1, "res/brick_wall.png"));
	Scene::add("player", *player);
	createLevel();

//	std::vector<std::pair<float, float>> points;
//	points.push_back(std::make_pair(1.0f, 1.0f));
//	points.push_back(std::make_pair(3.0f, 3.0f));
//	points.push_back(std::make_pair(8.0f, 1.5f));
//	points.push_back(std::make_pair(7.0f, 0.8f));
//	Entity *poly = new Entity(new SolidPolygon(points));
//	poly->addTag("wall");
//	Scene::add(*poly);
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
		transform.queueAnimation(1.0, Ease::backInOut).addComponent(1, &Transform::translateX);
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

	auto collision = Collider::intersection(Scene::get("player"), Scene::get("end"));
	if(collision.first != 0 && collision.second != 0)
	{
		createLevel();
	}

	Scene::get("player").collideByTag("wall");

	Scene::getCamera().getInverseTransform().setTranslation(transform.getDX(), transform.getDY());
}

void TestRunner::cleanup(){}
