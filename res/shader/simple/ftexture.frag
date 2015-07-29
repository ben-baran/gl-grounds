#version 330 core

in vec2 vTexCoord;
out vec4 color;
uniform sampler2D tex;

void main()
{
    color = texture(tex, vTexCoord);
    if(color.r < 0.5 && color.g < 0.5 && color.b < 0.5) discard;
    color.r = 0.3;
    color.g = 0.5;
    color.b = 0.3;
}