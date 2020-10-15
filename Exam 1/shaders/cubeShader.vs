#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec3 Color;
out vec2 UV;

uniform vec3 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Color = color;
    UV = aUV;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
