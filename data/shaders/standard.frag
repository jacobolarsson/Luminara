#version 460 core

in vec2 UV;

uniform sampler2D myTexture;

out vec4 FragColor;

void main()
{
    FragColor = texture(myTexture, UV);
} 