#pragma once

#include <string>
#include <glm/glm.hpp>

struct ShaderProgram
{
	unsigned int id;
	enum ShaderType { Vertex, Fragment };

	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	std::string loadShaderCode(const char* filename) const;
	unsigned int createShader(const char* filename, ShaderType type) const;
	void use() const;
	void setFloat(const char* name, float value) const;
	void setInt(const char* name, int value) const;
	void setMat4(const char* name, const glm::mat4& value) const;
	void setVec3(const char* name, const glm::vec3& value) const;
};

