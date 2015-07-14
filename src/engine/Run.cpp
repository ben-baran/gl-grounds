#include <src/engine/util/Window.hpp>

#include "Scene.hpp"
#include "Run.hpp"

using std::string;

Run::Run(string title)
{
	Window::init(title, false, 600, 600);
	setup();

	Window::start(baseUpdate);

	cleanup();
	glfwTerminate();
}

void Run::baseUpdate(double dt)
{
	Scene::update(dt);
	update(dt);
	Scene::draw();
	Scene::updateBuffers();
}
