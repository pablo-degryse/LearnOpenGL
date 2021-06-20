#pragma once

#include <string>
#include <glm/glm.hpp>

struct ShaderProgram
{
	unsigned int Id;
	enum ShaderType { Vertex, Fragment };

	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	std::string loadShaderCode(const char* filename) const;
	unsigned int createShader(const char* filename, ShaderType type) const;
	void use() const;
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;
};

