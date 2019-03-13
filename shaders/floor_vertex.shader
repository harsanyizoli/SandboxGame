#version 330 core
layout (location = 2) in vec3 aPos;
layout (location = 3) in vec2 aTexCord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 outColor;
out vec2 TexCord;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
    outColor = vec3(1.0f, 1.0f, 1.0f);
    TexCord = aTexCord;

}