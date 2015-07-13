#pragma once

#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include "../render/Texture.hpp"

class Res
{
private:
    static std::unordered_map<std::string, std::string> loadedStrings;
    static std::unordered_map<std::string, Texture> loadedTextures;
    static std::unordered_map<std::string, Shader> loadedShaders;
public:
    static std::string *loadStr(const std::string &name, const std::string &file = "");
    static Texture *loadTex(const std::string &name, const std::string &file = "");
    static Shader *loadShader(const std::string &name, const std::string &file = "");
};