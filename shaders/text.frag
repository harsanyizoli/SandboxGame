#version 330 core

in vec2 TextCoords;
out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
    //FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    FragColor = texture(Texture, TextCoords);
}