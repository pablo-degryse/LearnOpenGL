#include <iostream>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"

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
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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

	float vertices[] = {
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top 
	};

	unsigned int vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	int maxAttribs = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttribs);
	std::cout << "Max nr of supported vertex attribs: " << maxAttribs << std::endl;

	ShaderProgram shaderProgram("Res/Shaders/Vertex.glsl", "Res/Shaders/Fragment.glsl");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		shaderProgram.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}