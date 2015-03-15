#pragma once

#include <unordered_map>
#include <string>
#include <GL/glew.h>

class Res
{
private:
    static std::unordered_map<std::string, std::string> loadedStrings;
    static std::unordered_map<std::string, GLuint> loadedTextures;
    static int PNG_HEADER_BYTES;
public:
    static const std::string *loadStr(const std::string &name, const std::string &file = "");
    static const GLuint *loadTex(const std::string &name, const std::string &file = "");
};