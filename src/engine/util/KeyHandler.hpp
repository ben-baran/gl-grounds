#pragma once

#include <GLFW/glfw3.h>

class KeyHandler
{
public:
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
};
