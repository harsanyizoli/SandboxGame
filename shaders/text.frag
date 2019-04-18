#version 330 core
in vec2 TexCoords;
uniform sampler2D aTexture;
void main()
{
    FragColor = texture(aTexture, TexCoords);
}