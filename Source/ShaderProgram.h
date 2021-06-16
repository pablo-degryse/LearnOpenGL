#pragma once

#include <string>
#include <glm/glm.hpp>

class ShaderProgram
{
private:
	enum ShaderType { Vertex, Fragment };
	std::string loadShaderCode(const char* filename) const;
	unsigned int createShader(const char* filename, ShaderType type) const;
public:
	unsigned int Id;
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	void use() const;
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;
};

