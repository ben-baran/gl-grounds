#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>

#include "Res.h"
#include "VAO.h"
#include "Shader.h"
#include "Window.h"

using namespace glm;

Shader *shader;
VAO *vao;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void loop(double dt)
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    vao->draw();
}

int main()
{
    GLFWwindow *window = Window::init("Engine V1", false, 1280, 720);
    glfwSetKeyCallback(window, key_callback);

    Res::loadTex("res/brick_wall.png");
    shader = new Shader(*Res::loadStr("res/shader/default.v"), *Res::loadStr("res/shader/default.f"));

    GLfloat vertices[] = {
             1.0f,  1.0f, 0.0f, /* COLOR */ 1.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 0.0f,             0.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,             1.0f, 0.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,             0.0f, 0.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    int attributes[2]{3, 3};

    vao = new VAO(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);

    Window::start(loop);

    vao->clean();
    shader->clean();
    delete vao;
    delete shader;
    glfwTerminate();
    return 0;
}