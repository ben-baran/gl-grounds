#include "Window.hpp"
#include "KeyHandler.hpp"
#include "MouseHandler.hpp"
#include <iostream>

int Window::refresh = REFRESH_RATE_DEFAULT;
int Window::windowX = -1, Window::windowY = -1;
int Window::pixelX = -1, Window::pixelY = -1;
GLFWwindow *Window::window;
void (*Window::handler)(double);
bool Window::paused;

GLFWwindow *Window::init(const std::string &title, bool fullscreen, int resX, int resY)
{
    refresh = REFRESH_RATE_DEFAULT;
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
	windowX = resX;
	windowY = resY;

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

    int pixelX, pixelY;
    glfwGetFramebufferSize(window, &pixelX, &pixelY);
    glViewport(0, 0, pixelX, pixelY);

	Window::pixelX = pixelX;
	Window::pixelY = pixelY;

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glfwSetKeyCallback(window, KeyHandler::callback);
    glfwSetMouseButtonCallback(window, MouseHandler::buttonCallback);
	glfwSetCursorPosCallback(window, MouseHandler::moveCallback);

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

			glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

int Window::getWindowX()
{
	return windowX;
}

int Window::getWindowY()
{
	return windowY;
}

int Window::getPixelX()
{
    return pixelX;
}

int Window::getPixelY()
{
    return pixelY;
}
