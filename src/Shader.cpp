#include "Shader.hpp"
#include <iostream>

using std::string;

Shader::Shader(const string &vSource, const string &fSource)
{
    GLint success;
    GLchar infoLog[512];

    const GLchar *vShaderChars = vSource.c_str(), *fShaderChars = fSource.c_str();

    //Creating the vertex shader

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderChars, nullptr);
    glCompileShader(vShader);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vShader, 512, nullptr, infoLog);
        std::cout << "Failed to compile vertex shader: \n" << infoLog << std::endl;
    }

    //Creating the fragment shader

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderChars, nullptr);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fShader, 512, nullptr, infoLog);
        std::cout << "Failed to compile fragment shader: \n" << infoLog << std::endl;
    }

    //Linking the shaders

    program = glCreateProgram();

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Failed to link program: \n" << infoLog << std::endl;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::use()
{
    glUseProgram(program);
}

void Shader::clean()
{
    glDeleteProgram(program);
}

GLint Shader::getLocation(const string &name) const
{
    return glGetUniformLocation(program, name.c_str());
}