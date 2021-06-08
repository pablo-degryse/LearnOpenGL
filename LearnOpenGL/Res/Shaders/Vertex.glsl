#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_texCoord;

out vec3 ourColor;
out vec2 texCoord;

void main()
{
	gl_Position = vec4(a_pos, 1.0f);
	ourColor = a_color;
	texCoord = a_texCoord;
}