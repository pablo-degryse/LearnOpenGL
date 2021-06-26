#include <iostream>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Input.h"
#include "FpsCamera.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Buffers.h"
#include "VertexArray.h"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static bool g_wireframeModeEnabled = false;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F8 && action == GLFW_PRESS)
	{
		if (g_wireframeModeEnabled)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		g_wireframeModeEnabled = !g_wireframeModeEnabled;
	}
	else if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void processInput(GLFWwindow* window, Input& input)
{
	input.moveForward = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
	input.moveBackward = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
	input.moveLeft = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
	input.moveRight = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);

	double xPos = 0.0, yPos = 0.0;
	glfwGetCursorPos(window, &xPos, &yPos);
	if(!input.mousePosInitialized)
	{
		input.lastMouseX = (float)xPos;
		input.lastMouseY = (float)yPos;
		input.mousePosInitialized = true;
	}

	input.mouseMoveX = (float)xPos - input.lastMouseX;
	input.mouseMoveY = input.lastMouseY - (float)yPos; // inverse
	input.lastMouseX = (float)xPos;
	input.lastMouseY = (float)yPos;

	input.scrollDiff = input.currentScroll - input.lastScroll;
	input.lastScroll = input.currentScroll;
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	Input* input = (Input*)glfwGetWindowUserPointer(window);
	input->currentScroll += (float)yOffset;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "failed to create window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
		std::cout << "failed to load OpenGL functions\n";
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetScrollCallback(window, scrollCallback);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	VertexAttribute cubeVertexAttribs[] = {
		VertexAttribute(3, 0),
		VertexAttribute(3, 3)
	};
	VertexAttribute lightVertexAttribs[] = {
		VertexAttribute(3, 0)
	};
	
	VertexBuffer vbo(vertices, 216, GL_STATIC_DRAW);
	VertexAttributeDescriptor cubeAttribsDesc(cubeVertexAttribs, 2, 6);
	VertexArray cubeVao(GL_TRIANGLES, 36, false);
	cubeVao.bind();
	cubeVao.RegisterVertexBufferAttributes(vbo, cubeAttribsDesc);

	VertexAttributeDescriptor lightAttribsDesc(lightVertexAttribs, 1, 6);
	VertexArray lightVao(GL_TRIANGLES, 36, false);
	lightVao.bind();
	lightVao.RegisterVertexBufferAttributes(vbo, lightAttribsDesc);

	ShaderProgram lightShaderProgram("Res/Shaders/LightVertex.glsl", 
		"Res/Shaders/LightFragment.glsl");
	ShaderProgram cubeShaderProgram("Res/Shaders/cubeVertex.glsl", 
		"Res/Shaders/cubeFragment.glsl");

	glEnable(GL_DEPTH_TEST);

	// camera & input stuff
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Input input = {0};
	glfwSetWindowUserPointer(window, (void*)&input);
	FpsCamera camera(glm::vec3(0.0f, 0.0f, 3.0f), 45.0f);
	float lastTime = (float)glfwGetTime();
	float deltaTime = 0.0f;

	glm::vec3 lightPos(1.2f, 2.0f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glfwPollEvents();
		processInput(window, input);
		camera.processInput(input, deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.updateViewMat();
		camera.updateProjMat();
		
		cubeVao.bind();
		cubeShaderProgram.use();
		cubeShaderProgram.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		cubeShaderProgram.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		cubeShaderProgram.setMat4("view", camera.viewMat);
		cubeShaderProgram.setMat4("projection", camera.projMat);
		glm::mat4 model = glm::mat4(1.0f);
		cubeShaderProgram.setMat4("model", model);
		cubeShaderProgram.setVec3("lightPos", lightPos);
		cubeShaderProgram.setVec3("viewPos", camera.position);
		glDrawArrays(cubeVao.primitiveType, 0, cubeVao.nrOfElements);

		lightVao.bind();
		lightShaderProgram.use();
		lightShaderProgram.setMat4("view", camera.viewMat);
		lightShaderProgram.setMat4("projection", camera.projMat);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShaderProgram.setMat4("model", model);
		glDrawArrays(lightVao.primitiveType, 0, lightVao.nrOfElements);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}