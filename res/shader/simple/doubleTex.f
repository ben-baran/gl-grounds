#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 color;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    color = mix(texture(tex1, vTexCoord), texture(tex2, vTexCoord, 0.5);
}