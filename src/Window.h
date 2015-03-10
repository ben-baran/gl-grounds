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

    static GLFWwindow *init(std::string title, bool fullscreen, int resX = -1, int resY = -1);
    static GLFWwindow *getWindow();

    static void start(void (*handler)(double));
    static void setPaused(bool paused);
    static void end();
private:
    static constexpr int REFRESH_RATE_DEFAULT = 60;
    static int refresh;
    static int resX, resY;
    static GLFWwindow *window;
    static void (*handler)(double);
    static bool paused;
};