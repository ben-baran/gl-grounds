#version 330 core

in vec2 vTexCoord;
out vec4 color;
uniform sampler2D tex;

void main()
{
    color = texture(tex, vTexCoord);
    if(color.r == 0 && color.g == 0 && color.b == 0) color.a = 0;
    color.r = 0.4;
    color.g = 0.6;
    color.b = 0.4;
}