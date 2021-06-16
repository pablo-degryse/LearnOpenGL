#version 330 core

in vec2 texCoord;
out vec4 o_fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	o_fragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.3f);
}