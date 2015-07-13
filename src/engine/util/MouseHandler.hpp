#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

class MouseHandler
{
private:
	static const double ALLOWED_PRESS_DELTA;
	static std::unordered_map<int, double> buttons;
	static double screenX, screenY;
public:
	static void buttonCallback(GLFWwindow *window, int button, int action, int mods);
	static void moveCallback(GLFWwindow *window, double x, double y);
};