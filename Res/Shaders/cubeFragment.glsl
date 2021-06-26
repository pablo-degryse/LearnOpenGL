#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;
out vec4 o_fragColor;

void main()
{
	o_fragColor = vec4(objectColor * lightColor, 1.0f);
}