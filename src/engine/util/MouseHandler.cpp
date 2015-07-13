#include "MouseHandler.hpp"

const double MouseHandler::ALLOWED_PRESS_DELTA = 0.16666;
std::unordered_map<int, double> MouseHandler::buttons;
double MouseHandler::pixelX, MouseHandler::pixelY;

void MouseHandler::buttonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if(action == GLFW_PRESS) buttons[button] = glfwGetTime();
	else if(action == GLFW_RELEASE) buttons.erase(button);
}

void MouseHandler::moveCallback(GLFWwindow *window, double x, double y)
{
	pixelX = x;
	pixelY = y;
}

bool MouseHandler::pressed(int button)
{
	auto find = buttons.find(button);
	bool has = find != buttons.end();
	if(has && glfwGetTime() - find->second < ALLOWED_PRESS_DELTA)
	{
		buttons.erase(find);
		return true;
	}
	if(has) buttons.erase(find);
	return false;
}

bool MouseHandler::held(int button)
{
	return buttons.find(button) != buttons.end();
}

double MouseHandler::getPixelX()
{
	return pixelX;
}

double MouseHandler::getPixelY()
{
	return pixelY;
}
