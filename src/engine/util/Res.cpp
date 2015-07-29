#include "Res.hpp"
#include <fstream>
#include <iostream>
#include <SOIL/SOIL.h>

using std::unordered_map;
using std::string;
using std::ifstream;

unordered_map<string, string> Res::loadedStrings;
unordered_map<string, Texture> Res::loadedTextures;
unordered_map<string, Shader> Res::loadedShaders;

string *Res::loadStr(const string &name, const string &file)
{
    if(file == "") return loadStr(name, name);
    if(loadedStrings.find(name) != loadedStrings.end()) return &loadedStrings[name];

    ifstream f(file);
    if(f.is_open())
    {
        string line, total;
        while(std::getline(f, line)) total += line + "\n";
        loadedStrings[name] = total;

        f.close();
        return &loadedStrings[name];
    }
    return nullptr;
}

Texture *Res::loadTex(const string &name, const string &file)
{
    if(file == "") return loadTex(name, name);
    if(loadedTextures.find(name) != loadedTextures.end()) return &loadedTextures[name];

    ifstream f(file);
    if(f.is_open())
    {
        Texture tex;
        unsigned char *data = SOIL_load_image(file.c_str(), &tex.width, &tex.height, 0, SOIL_LOAD_RGBA);

        glGenTextures(1, &tex.id);
        glBindTexture(GL_TEXTURE_2D, tex.id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        SOIL_free_image_data(data);
        glBindTexture(GL_TEXTURE_2D, 0);

        loadedTextures[name] = tex;
        return &loadedTextures[name];
    }

    return nullptr;
}

Shader *Res::loadShader(const string &name, const string &file)
{
    if(file == "") return loadShader(name, name);

    unordered_map<string, Shader>::iterator find = loadedShaders.find(name);
    if(find != loadedShaders.end()) return &(find->second);

    loadedShaders.insert(std::make_pair<string, Shader>((string) name,
                                                        (Shader) (*(new Shader(*loadStr(file + ".vert"), *loadStr(file + ".frag"))))));
    return &(loadedShaders.find(name)->second);

    return nullptr;
}
