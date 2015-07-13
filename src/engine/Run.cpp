#include <src/engine/util/Window.hpp>
#include "Run.hpp"

using std::string;

Run::Run(string title)
{
	Window::init(title, false, 600, 600);
	setup();

	Window::start(update);

	cleanup();
	glfwTerminate();
}
