#version 330 core
layout (location = 2) in vec3 aPos;
layout (location = 3) in vec2 aTexCord;

uniform mat4 matrix;

out vec4 FragColor;
out vec2 TextCoords;

void main() {
    gl_Position = matrix * vec4(aPos, 1.0f);
	TextCoords = aTexCord;
}