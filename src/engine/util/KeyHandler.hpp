#pragma once

#include <GLFW/glfw3.h>
#include <unordered_set>

class KeyHandler
{
private:
	static std::unordered_set<int> pressed, held;
public:
	static void clearPressed();
	static void callback(GLFWwindow *window, int key, int scancode, int action, int mode);
};
