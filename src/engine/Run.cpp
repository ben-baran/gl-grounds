#include <src/engine/util/Window.hpp>

#include "Scene.hpp"
#include "Run.hpp"

using std::string;

Run *Run::currentRun;

void Run::start(Run *run)
{
	srand(time(nullptr));
	currentRun = run;
	Window::init("Title", true, -1, -1);
	Scene::getCamera().getInverseTransform().setScale(9 * Window::getPixelX() / ((double) Window::getPixelY()), 9);

	run->setup();

	Scene::updateBuffers();
	Window::start(baseUpdate);

	run->cleanup();
	glfwTerminate();
}

void Run::baseUpdate(double dt)
{
	Scene::update(dt);
	currentRun->update(dt);
	Scene::updateBuffers();
	Scene::draw();
}

void Run::end()
{
	cleanup();
	glfwSetWindowShouldClose(Window::getWindow(), GL_TRUE);
}
