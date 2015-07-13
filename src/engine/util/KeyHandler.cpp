//
// Created by Benjamin Barantschik on 7/13/15.
//

#include "KeyHandler.hpp"

void KeyHandler::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
