#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    enum Type
    {
        FULLSCREEN,
        BORDERLESS,
        NORMAL
    };

    static GLFWwindow *init(const std::string &title, bool fullscreen, int resX = -1, int resY = -1);
    static GLFWwindow *getWindow();

    static void start(void (*handler)(double));
    static void setPaused(bool paused);
    static void end();
	static int getWindowX();
	static int getWindowY();
    static int getPixelX();
	static int getPixelY();
private:
    static constexpr int REFRESH_RATE_DEFAULT = 60;
    static int refresh;
    static int windowX, windowY, pixelX, pixelY;
    static GLFWwindow *window;
    static void (*handler)(double);
    static bool paused;
};