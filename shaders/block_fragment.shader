#version 330 core
out vec4 FragColor;
uniform float blueValue;
in vec3 outColor;

void main()
{
	FragColor = vec4(outColor.x, outColor.y, blueValue, 1.0f);
}