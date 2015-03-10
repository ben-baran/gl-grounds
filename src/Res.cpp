#include "Res.h"
#include <fstream>
#include <iostream>

using std::unordered_map;
using std::string;
using std::ifstream;

unordered_map<string, string> Res::loadedStrings;
unordered_map<string, GLuint> Res::loadedTextures;

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

const GLuint *Res::loadTex(const string &name, const string &file)
{
    if(file == "") return loadTex(name, name);

    unordered_map<string, GLuint>::const_iterator find = loadedTextures.find(name);
    if(find != loadedTextures.end()) return &(find->second);

    ifstream f(file, std::ios::binary);
    if(f.is_open())
    {
        char header[8];
        f.read(header, 8);
        std::cout << ((uint) header[0]) << " " << ((int) header[1]) << std::endl;

        f.close();
    }

    return nullptr;
}
