#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <src/engine/render/Transform.hpp>
#include "engine/render/SolidRectangle.hpp"

#include "engine/util/Window.hpp"

//New way
SolidRectangle *rect;
Transform *transform;
//Not needed anymore
//Shader *shader;
//VAO *vao;
//Texture *texture;

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

    //New way
    rect->draw(transform);

    //Old way
//    texture->use(*shader, "tex");
//    shader->use();
//
//    glm::mat4 trans;
//    trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//    trans = glm::scale(trans, glm::vec3(0.8f + 0.2f * sin(4 * glfwGetTime()), 0.8f + 0.2f * sin(4 * glfwGetTime()), 1.0f));
//    trans = glm::translate(trans, glm::vec3(0, 0.5f * sin(glfwGetTime() * 2.5f), 0.0f));
//    glUniformMatrix4fv(shader->getLocation("transform"), 1, GL_FALSE, glm::value_ptr(trans));
//
//    vao->draw();

}

int main()
{
    GLFWwindow *window = Window::init("Engine 0.1", false, 500, 500);
    glfwSetKeyCallback(window, key_callback);

    //New way
    rect = new SolidRectangle(-0.5, -0.5, 1, 1, 0.5, 0.5, 0.9);
	transform = new Transform();
	transform->rotate(45 * 3.141592f / 180);

    //Old way
//    texture = Res::loadTex("res/brick_wall.png");
//    shader = Res::loadShader("res/shader/simple/textureColor");
//
//    GLfloat vertices[] = {
//             0.5f,  0.5f, 0.0f, /* COLOR */ 1.0f, 0.0f, 0.0f, /* TEXTURE */ 1.0f, 1.0f,
//             0.5f, -0.5f, 0.0f,             0.0f, 1.0f, 0.0f,               1.0f, 0.0f,
//            -0.5f, -0.5f, 0.0f,             1.0f, 0.0f, 0.0f,               0.0f, 0.0f,
//            -0.5f,  0.5f, 0.0f,             0.0f, 0.0f, 1.0f,               0.0f, 1.0f
//    };
//
//    GLuint indices[] = {
//            0, 1, 3,
//            1, 2, 3
//    };
//
//    int attributes[3]{3, 3, 2};
//
//    vao = new VAO(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);

    Window::start(loop);

    //New way
    delete rect;

    //Old way
//    vao->clean();
//    shader->clean();
//    delete vao;
//    delete shader;
    glfwTerminate();
    return 0;
}