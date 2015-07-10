#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "engine/Res.hpp"
#include "engine/VAO.hpp"
#include "engine/Shader.hpp"
#include "engine/Window.hpp"

Shader *shader;
VAO *vao;
const Texture *texture;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void loop(double dt)
{
    glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
    glClear(GL_COLOR_BUFFER_BIT);

    texture->use(*shader, "tex");
    shader->use();

    glm::mat4 trans;
    trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.8f + 0.2f * sin(4 * glfwGetTime()), 0.8f + 0.2f * sin(4 * glfwGetTime()), 1.0f));
    trans = glm::translate(trans, glm::vec3(0, 0.5f * sin(glfwGetTime() * 2.5f), 0.0f));
    glUniformMatrix4fv(shader->getLocation("transform"), 1, GL_FALSE, glm::value_ptr(trans));

    vao->draw();
}

int main()
{
    GLFWwindow *window = Window::init("Engine 0.1", false, 500, 500);
    glfwSetKeyCallback(window, key_callback);

    texture = Res::loadTex("res/brick_wall.png");
    shader = new Shader(*Res::loadStr("res/shader/simple/textureColor.vert"), *Res::loadStr("res/shader/simple/textureColor.frag"));

    GLfloat vertices[] = {
             0.5f,  0.5f, 0.0f, /* COLOR */ 1.0f, 0.0f, 0.0f, /* TEXTURE */ 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,             0.0f, 1.0f, 0.0f,               1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,             1.0f, 0.0f, 0.0f,               0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,             0.0f, 0.0f, 1.0f,               0.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    int attributes[3]{3, 3, 2};

    vao = new VAO(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);

    Window::start(loop);

    vao->clean();
    shader->clean();
    delete vao;
    delete shader;
    glfwTerminate();
    return 0;
}