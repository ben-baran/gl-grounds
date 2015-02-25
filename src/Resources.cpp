#include "Resources.h"
#include <fstream>

using std::unordered_map;
using std::string;
using std::ifstream;

unordered_map<string, string> Res::loadedFiles;

const string* Res::loadStr(string name)
{
    unordered_map<string, string>::const_iterator find = loadedFiles.find(name);
    if(find != loadedFiles.end()) return &(find->second);

    ifstream f(name);
    if(f.is_open())
    {
        string line, total;
        while(std::getline(f, line)) total += line + "\n";
        loadedFiles[name] = total;

        f.close();
        return &(loadedFiles.find(name)->second);
    }
    return nullptr;
}
