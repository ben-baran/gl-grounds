//
// Created by Benjamin Barantschik on 7/13/15.
//

#include "KeyHandler.hpp"

std::unordered_set<int> KeyHandler::pressed, KeyHandler::held;

void KeyHandler::clearPressed()
{
	pressed.clear();
}

void KeyHandler::callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if(action == GLFW_PRESS)
	{
		pressed.insert(key);
		held.insert(key);
	}
	else if(action == GLFW_RELEASE)
	{
		pressed.emplace(key);
		held.emplace(key);
	}
}