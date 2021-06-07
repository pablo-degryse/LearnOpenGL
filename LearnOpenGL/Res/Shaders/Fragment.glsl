#version 330 core
out vec4 o_fragColor;
in vec3 ourColor;
void main()
{
	o_fragColor = vec4(ourColor, 1.0f);
}