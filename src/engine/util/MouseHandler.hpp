#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

class MouseHandler
{
private:
	static const double ALLOWED_PRESS_DELTA;
	static std::unordered_map<int, double> buttons;
	static double pixelX, pixelY;
public:
	static void buttonCallback(GLFWwindow *window, int button, int action, int mods);
	static void moveCallback(GLFWwindow *window, double x, double y);

	static bool pressed(int button);
	static bool held(int button);
	static std::pair<double, double> getPixelCoords();
	static std::pair<double, double> getWorldCoords();
};