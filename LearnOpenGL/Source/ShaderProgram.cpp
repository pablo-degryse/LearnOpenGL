#include "ShaderProgram.h"

#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <glm/gtc/type_ptr.hpp>

std::string ShaderProgram::loadShaderCode(const char* filename) const
{
	auto file = std::ifstream(filename);
	assert(!file.fail());
	std::stringstream stringStream;
	stringStream << file.rdbuf();
	file.close();
	return stringStream.str();
}

unsigned int ShaderProgram::createShader(const char* filename, ShaderType type) const
{
	std::string code = loadShaderCode(filename);
	unsigned int shader;
	switch (type)
	{
	case ShaderType::Vertex:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::Fragment:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		assert(false);
		break;
	}
	const char* codePtr = code.c_str();
	glShaderSource(shader, 1, &codePtr, nullptr);
	glCompileShader(shader);

	int shaderCompileSuccess = 0;
	char shaderInfoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompileSuccess);
	if (!shaderCompileSuccess) {
		glGetShaderInfoLog(shader, 512, nullptr, shaderInfoLog);
		std::cout << "Shader compilation error:\n" << shaderInfoLog << std::endl;
	}
	return shader;
}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	unsigned int vertexShader = createShader(vertexFile, ShaderType::Vertex);
	unsigned int fragmentShader = createShader(fragmentFile, ShaderType::Fragment);
	
	Id = glCreateProgram();
	glAttachShader(Id, vertexShader);
	glAttachShader(Id, fragmentShader);
	glLinkProgram(Id);

	int programLinkSuccess = 0;
	char programInfoLog[512];
	glGetProgramiv(Id, GL_LINK_STATUS, &programLinkSuccess);
	if (!programLinkSuccess) {
		glGetProgramInfoLog(Id, 512, nullptr, programInfoLog);
		std::cout << "Program link error:\n" << programInfoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::use() const
{
	glUseProgram(Id);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
	int loc = glGetUniformLocation(Id, name.c_str());
	glUniform1f(loc, value);
}

void ShaderProgram::setInt(const std::string& name, int value) const
{ 
	int loc = glGetUniformLocation(Id, name.c_str());
	glUniform1i(loc, value);
}

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& value) const
{
	int loc = glGetUniformLocation(Id, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}
