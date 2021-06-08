#pragma once

#include <string>

class ShaderProgram
{
private:
	enum ShaderType { Vertex, Fragment };
	std::string loadShaderCode(const char* filename);
	unsigned int createShader(const char* filename, ShaderType type);
public:
	unsigned int Id;
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	void use();
	void setFloat(const std::string& name, float value);
	void setInt(const std::string& name, int value);
};

