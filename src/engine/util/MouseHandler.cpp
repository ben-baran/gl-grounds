#include "MouseHandler.hpp"

const double MouseHandler::ALLOWED_PRESS_DELTA = 0.16666;
std::unordered_map<int, double> MouseHandler::buttons;

void MouseHandler::buttonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if(action == GLFW_PRESS) buttons[button] = glfwGetTime();
	else if(action == GLFW_RELEASE) buttons.erase(button);
}

void MouseHandler::moveCallback(GLFWwindow *window, double x, double y)
{
	screenX = x;
	screenY = y;
}
