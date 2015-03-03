#include <string>
#include <GL/glew.h>

class Shader
{
private:
    GLuint program;
public:
    Shader(const std::string &vsource, const std::string &fsource);
    void use();
    void clean();
};