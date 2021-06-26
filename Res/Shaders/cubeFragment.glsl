#version 330 core

in vec3 p_normal;
in vec3 p_fragPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
out vec4 o_fragColor;

void main()
{
	float ambientLightStrength = 0.1f;
	vec3 ambientLight = lightColor * ambientLightStrength;

	vec3 norm = normalize(p_normal);
	vec3 lightDir = normalize(lightPos - p_fragPos);
	float lightToFragAngle = max(dot(norm, lightDir), 0.0f);
	vec3 diffuseLight = lightColor * lightToFragAngle;

	float specularity = 0.5f;
	vec3 viewDir = normalize(viewPos - p_fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
	vec3 specularLight = specularity * spec * lightColor;

	o_fragColor = vec4(objectColor * (ambientLight + diffuseLight + specularLight), 1.0f);
}