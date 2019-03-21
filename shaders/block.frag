#version 330 core
out vec4 FragColor;

uniform sampler2D ourTexture;

in vec3 outColor;
in vec2 TexCord;

void main()
{
	FragColor = texture(ourTexture, TexCord);
	//FragColor = vec4(outColor, 1.0f);
}