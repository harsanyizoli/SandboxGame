#version 330 core
out vec4 FragColor;

uniform sampler2D ourTexture;

in vec3 outColor;

void main()
{
	//FragColor = texture(ourTexture, TexCord);
	FragColor = vec4(outColor, 1.0f);
}