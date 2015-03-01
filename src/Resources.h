#pragma once

#include <unordered_map>
#include <string>
#include <GL/glew.h>

class Res
{
private:
    static std::unordered_map<std::string, std::string> loadedFiles;
public:
    static const std::string* loadStr(std::string name);
};