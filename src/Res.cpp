#include "Res.h"
#include <fstream>
#include <iostream>
#include "png.h"

using std::unordered_map;
using std::string;
using std::ifstream;

unordered_map<string, string> Res::loadedStrings;
unordered_map<string, GLuint> Res::loadedTextures;
int Res::PNG_HEADER_BYTES = 8;

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

    ifstream f(file);
    if(f.is_open())
    {
        if(strcmp(&file[file.length() - 4], ".png") == 0)
        {
            png_byte signature[PNG_HEADER_BYTES];
            int valid = 0;
            f.read((char *) signature, PNG_HEADER_BYTES);
            if(!f.good()) return nullptr;
            valid = png_sig_cmp(signature, 0, PNG_HEADER_BYTES);

            if(valid == 0)
            {
                png_structp readStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
                png_infop infoStruct = png_create_info_struct(readStruct);

                png_set_sig_bytes(readStruct, PNG_HEADER_BYTES);
                png_read_info(readStruct, infoStruct);

            }
        }
    }

    return nullptr;
}