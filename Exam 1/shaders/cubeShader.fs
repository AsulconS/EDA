#version 330 core

in vec3 Color;
in vec2 UV;

out vec4 FragColor;

uniform sampler2D texture0;

void main()
{
    vec4 textureColor = texture(texture0, UV);

    FragColor = vec4(Color * textureColor.xyz, 0.125f);
}
