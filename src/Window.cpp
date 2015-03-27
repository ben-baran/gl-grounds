#include "Window.hpp"
#include <iostream>

int Window::refresh = REFRESH_RATE_DEFAULT;
int Window::resX = -1, Window::resY = -1;
GLFWwindow *Window::window;
void (*Window::handler)(double);
bool Window::paused;

GLFWwindow *Window::init(const std::string &title, bool fullscreen, int resX, int resY)
{
    refresh = REFRESH_RATE_DEFAULT;
    Window::resX = resX;
    Window::resY = resY;
    paused = false;

    if(!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    if(resX == -1 || resY == -1)
    {
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        resX = mode->width;
        resY = mode->height;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if(fullscreen) window = glfwCreateWindow(resX, resY, title.c_str(), monitor, nullptr);
    else window = glfwCreateWindow(resX, resY, title.c_str(), nullptr, nullptr);

    if(!window)
    {
        std::cout << "Failed to open GLFW window" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return nullptr;
    }

    glViewport(0, 0, resX, resY);

    return window;
}

GLFWwindow *Window::getWindow()
{
    return window;
}

void Window::start(void (*handler)(double))
{
    Window::handler = handler;
    double lastTime = glfwGetTime();
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if(!paused)
        {
            double time = glfwGetTime();
            handler(time - lastTime);
            lastTime = time;
            glfwSwapBuffers(window);
        }
    }
}

void Window::setPaused(bool paused)
{
    Window::paused = paused;
}

void Window::end()
{
    glfwDestroyWindow(window);
}
