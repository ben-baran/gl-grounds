#pragma once

#include <GLFW/glfw3.h>
#include <unordered_set>

class KeyHandler
{
private:
	static std::unordered_set<int> pressedSet, heldSet;
public:
	static void clearPressed();
	static void callback(GLFWwindow *window, int key, int scancode, int action, int mode);

	static bool pressed(int key);
	static bool held(int key);
};
