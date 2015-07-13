#include "KeyHandler.hpp"

const double KeyHandler::ALLOWED_PRESS_DELTA = 0.16666;
std::unordered_map<int, double> KeyHandler::keys;

void KeyHandler::callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if(action == GLFW_PRESS) keys[key] = glfwGetTime();
	else if(action == GLFW_RELEASE) keys.erase(key);
}

bool KeyHandler::pressed(int key)
{
	auto find = keys.find(key);
	bool has = find != keys.end();
	if(has && find->second < ALLOWED_PRESS_DELTA)
	{
		keys.erase(find);
		return true;
	}
	keys.erase(find);
	return false;
}

bool KeyHandler::held(int key)
{
	return keys.find(key) != keys.end();
}
