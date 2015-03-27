#pragma once

#include <unordered_map>
#include <string>
#include <GL/glew.h>
#include "Texture.hpp"

class Res
{
private:
    static std::unordered_map<std::string, std::string> loadedStrings;
    static std::unordered_map<std::string, Texture> loadedTextures;
public:
    static const std::string *loadStr(const std::string &name, const std::string &file = "");
    static const Texture *loadTex(const std::string &name, const std::string &file = "");
};