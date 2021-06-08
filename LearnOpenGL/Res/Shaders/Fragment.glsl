#version 330 core

in vec3 ourColor;
in vec2 texCoord;
out vec4 o_fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	o_fragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(1.0f - texCoord.x, texCoord.y)), 0.3f);
}