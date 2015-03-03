#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Resources.h"
#include "VAO.h"

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

    GLuint vShader, fShader;

    {
        //Making the vertex shader
        const GLchar *vShaderChars = Res::loadStr("res/shader/default.v")->c_str();

        vShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vShader, 1, &vShaderChars, nullptr);
        glCompileShader(vShader);

        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vShader, 512, nullptr, infoLog);
            std::cout << "Failed to compile vertex shader: \n" << infoLog << std::endl;
        }
    }

    {
        //Making the fragment shader
        const GLchar *fShaderChars = Res::loadStr("res/shader/default.f")->c_str();

        fShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fShader, 1, &fShaderChars, nullptr);
        glCompileShader(fShader);

        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fShader, 512, nullptr, infoLog);
            std::cout << "Failed to compile fragment shader: \n" << infoLog << std::endl;
        }
    }

    GLuint shaderProgram = glCreateProgram();

    {
        //Linking the program

        glAttachShader(shaderProgram, vShader);
        glAttachShader(shaderProgram, fShader);
        glLinkProgram(shaderProgram);

        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cout << "Failed to link program: \n" << infoLog << std::endl;
        }

        glDeleteShader(vShader);
        glDeleteShader(fShader);
    }

    int attributes[2]{3, 3};
    VAO vao(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        vao.draw();

        glfwSwapBuffers(window);
    }

    vao.clean();
    glfwTerminate();
    return 0;
}