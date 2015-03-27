#include "Res.h"
#include <fstream>
#include <iostream>
#include <SOIL/SOIL.h>

using std::unordered_map;
using std::string;
using std::ifstream;

unordered_map<string, string> Res::loadedStrings;
unordered_map<string, Texture> Res::loadedTextures;

const string *Res::loadStr(const string &name, const string &file)
{
    if(file == "") return loadStr(name, name);

    unordered_map<string, string>::const_iterator find = loadedStrings.find(name);
    if(find != loadedStrings.end()) return &(find->second);

    ifstream f(file);
    if(f.is_open())
    {
        string line, total;
        while(std::getline(f, line)) total += line + "\n";
        loadedStrings[name] = total;

        f.close();
        return &(loadedStrings.find(name)->second);
    }
    return nullptr;
}

const Texture *Res::loadTex(const string &name, const string &file)
{
    if(file == "") return loadTex(name, name);

    unordered_map<string, Texture>::const_iterator find = loadedTextures.find(name);
    if(find != loadedTextures.end()) return &(find->second);

    ifstream f(file);
    if(f.is_open())
    {
        Texture tex;
        unsigned char *data = SOIL_load_image(file.c_str(), &tex.width, &tex.height, 0, SOIL_LOAD_RGB);

        glGenTextures(1, &tex.id);
        glBindTexture(GL_TEXTURE_2D, tex.id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        SOIL_free_image_data(data);
        glBindTexture(GL_TEXTURE_2D, 0);

        loadedTextures[name] = tex;
        return &(loadedTextures.find(name)->second);
    }

    return nullptr;
}