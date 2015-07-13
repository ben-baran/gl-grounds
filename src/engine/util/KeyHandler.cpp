//
// Created by Benjamin Barantschik on 7/13/15.
//

#include "KeyHandler.hpp"

std::unordered_set<int> KeyHandler::pressedSet, KeyHandler::heldSet;

void KeyHandler::clearPressed()
{
	pressedSet.clear();
}

void KeyHandler::callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if(action == GLFW_PRESS)
	{
		pressedSet.insert(key);
		heldSet.insert(key);
	}
	else if(action == GLFW_RELEASE)
	{
		pressedSet.erase(key);
		heldSet.erase(key);
	}
}

bool KeyHandler::pressed(int key)
{
	return pressedSet.find(key) != pressedSet.end();
}

bool KeyHandler::held(int key)
{
	return heldSet.find(key) != heldSet.end();
}
