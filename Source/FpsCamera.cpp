#include "FpsCamera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

FpsCamera::FpsCamera(const glm::vec3& position, float fov)
    : position(position),
      up(0.0f, 1.0f, 0.0f),
      front(0.0f, 0.0f, -1.0f),
      yaw(-90.0f),
      pitch(0.0f),
      fov(fov),
      sensitivity(0.1f),
      speed(2.5f),
      viewMat(1.0f),
      projMat(1.0f)
{
}

void FpsCamera::processInput(const Input& input, float deltaTime)
{
    float movement = speed * deltaTime;
	if(input.moveForward)
		position += (front * movement);
	if(input.moveBackward)
		position -= (front * movement);
	if(input.moveLeft)
		position -= (glm::normalize(glm::cross(front, up)) * movement);
	if(input.moveRight)
		position += (glm::normalize(glm::cross(front, up)) * movement);

    yaw += input.mouseMoveX * sensitivity;
	pitch += input.mouseMoveY * sensitivity;

	if(pitch > 89.0f)
		pitch = 89.0f;
	else if(pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	);
	front = glm::normalize(direction);

    fov -= input.scrollDiff * 0.7f;
	if(fov < 20.0f)
		fov = 20.0f;
	else if(fov > 45.0f)
		fov = 45.0f;
}

void FpsCamera::updateViewMat()
{
    viewMat = glm::lookAt(position, position + front, up);
}

void FpsCamera::updateProjMat()
{
    projMat = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
}
