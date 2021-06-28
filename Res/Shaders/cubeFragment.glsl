#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shine;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 p_normal;
in vec3 p_fragPos;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

out vec4 o_fragColor;

void main()
{
	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(p_normal);
	vec3 lightDir = normalize(light.position - p_fragPos);
	float lightToFragAngle = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (lightToFragAngle * material.diffuse);

	float specularity = 0.5f;
	vec3 viewDir = normalize(viewPos - p_fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shine);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 objectColor = ambient + diffuse + specular;
	o_fragColor = vec4(objectColor, 1.0f);
}