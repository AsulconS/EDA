#version 330 core
#define  pointSize 32.0f

layout (location = 0) in vec3 aPos;

out vec3 Color;

uniform vec3 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Color = color;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_PointSize = pointSize;
}
