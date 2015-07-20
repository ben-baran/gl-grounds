#include "MouseHandler.hpp"
#include "Window.hpp"
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec4.hpp>
#include <src/engine/Scene.hpp>

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

std::pair<double, double> MouseHandler::getPixelCoords()
{
	return std::make_pair(pixelX, pixelY);
}

std::pair<double, double> MouseHandler::getWorldCoords()
{
	glm::vec4 coords(2 * (pixelX - Window::getWindowX() / 2) / Window::getWindowX(),
					 -2 * (pixelY - Window::getWindowY() / 2) / Window::getWindowY(), 0, 1);
	coords = Scene::getCamera().getInverseTransform().getMatrix() * coords;
	return std::make_pair(coords[0], coords[1]);
}
