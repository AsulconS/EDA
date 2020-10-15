#version 330 core

in vec3 Color;

out vec4 FragColor;

void main()
{
    vec2 circCoord = 8.0f * gl_PointCoord - 1.0f;
    if(dot(circCoord, circCoord) > 1.0f)
    {
        discard;
    }
    FragColor = vec4(Color, 1.0f);
}
