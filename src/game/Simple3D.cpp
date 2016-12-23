#include <src/engine/Entity.hpp>
#include <src/engine/render/Triangle.hpp>
#include <src/engine/Scene.hpp>
#include <src/engine/util/KeyHandler.hpp>
#include <src/engine/util/MouseHandler.hpp>
#include <iostream>
#include "Simple3d.hpp"

int main() {
    Run::start(new Simple3D());
}

void placeTri(float x, float y, float z) {
//    Triangle *triMesh = new Triangle(new float[9] {x, y + 0.25f, z, x - 0.25f, y - 0.25f, z, x + 0.25f, y - 0.25f, z});
//    Entity *tri = new Entity(triMesh);
//    tri->addTag("triangle");
//    Scene::add(*tri);
}

void Simple3D::setup() {
    for (int i = -5; i < 6; i++) {
        for (int j = -5; j < 6; j++) {
            placeTri(i, j, -10);
        }
    }
//    Entity *player = new Entity(new Triangle(new float[9] {0.0f, 0.1f, 0.0f, -0.2f, -0.1f, 0.0f, 0.1f, -0.1f, 0.0f}));
//    Scene::add("player", *player);
//    Scene::getCamera().attach(player);
//    player->set("controller", new SimpleController());
//    player->get<SimpleController>("controller").attach(player);
}

void Simple3D::update(double dt) {
    if (dt > 0.05) {
        std::cout << "dt: " << dt << std::endl;
    }
    if(KeyHandler::pressed(GLFW_KEY_ESCAPE)) end();

    Entity &player = Scene::get("player");
//    SimpleController &controller = player.get("controller");

    if(MouseHandler::pressed(GLFW_MOUSE_BUTTON_1)) {
        std::cout << "Clicked button 1" << std::endl;
//        std::cout << controller.x << " " << controller.y << " " << controller.z << std::endl;
    }

//    controller.rotateX(MouseHandler::movedX());
//    controller.rotateY(MouseHandler::movedY());

//    double speed = 0.08;
//    if(KeyHandler::held(GLFW_KEY_LEFT_SHIFT) || KeyHandler::held(GLFW_KEY_RIGHT_SHIFT)) speed *= 2;
//    if(KeyHandler::held(GLFW_KEY_W)) controller.movePointed(0.0f, 0.0f, speed);
//    if(KeyHandler::held(GLFW_KEY_A)) controller.movePointed(-speed, 0.0f, 0.0f);
//    if(KeyHandler::held(GLFW_KEY_S)) controller.movePointed(0.0f, 0.0f, -speed);
//    if(KeyHandler::held(GLFW_KEY_D)) controller.movePointed(speed, 0.0f, 0.0f);

//    player.collideByTag("tri");
}

void Simple3D::cleanup() {}

