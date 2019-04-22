#version 330 core
layout (location = 2) in vec3 aPos;
layout (location = 3) in vec2 aTexCord;

uniform mat4 model;
uniform mat4 projection;


out vec4 FragColor;
out vec2 TextCoords;

void main() {
    gl_Position = projection * model * vec4(aPos, 1.0f);
	TextCoords = aTexCord;
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}