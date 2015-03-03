#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Res.h"
#include "VAO.h"
#include "Shader.h"

using namespace glm;
using std::stringstream;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window;
    window = glfwCreateWindow(500, 500, "GLFW Test", nullptr, nullptr);

    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glViewport(0, 0, 500, 500);
    glfwSetKeyCallback(window, key_callback);

    GLfloat vertices[] = {
             0.5f,  0.5f, 0.0f, /* COLOR */ 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,             0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,             1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,             0.0f, 0.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    Shader shader(*Res::loadStr("res/shader/default.v"), *Res::loadStr("res/shader/default.f"));

    int attributes[2]{3, 3};
    VAO vao(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        vao.draw();

        glfwSwapBuffers(window);
    }

    vao.clean();
    shader.clean();
    glfwTerminate();
    return 0;
}