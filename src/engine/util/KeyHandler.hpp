#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

class KeyHandler
{
private:
	static const double ALLOWED_PRESS_DELTA;
	static std::unordered_map<int, double> keys;
public:
	static void callback(GLFWwindow *window, int key, int scancode, int action, int mode);

	static bool pressed(int key);
	static bool held(int key);
};
