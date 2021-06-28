#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 p_normal;
out vec3 p_fragPos;
out vec2 p_texCoords;

void main()
{
	gl_Position = projection * view * model * vec4(a_pos, 1.0f);
	p_normal = mat3(transpose(inverse(model))) * a_normal;
	p_fragPos = (model * vec4(a_pos, 1.0f)).xyz;
	p_texCoords = a_texCoords;
}