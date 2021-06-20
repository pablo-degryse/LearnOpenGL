#pragma once

#include <glm/glm.hpp>
#include "Input.h"

struct FpsCamera
{
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float fov;
    float sensitivity;
    float speed;
    glm::mat4 viewMat;
    glm::mat4 projMat;

    FpsCamera(const glm::vec3& position, float fov);
    void processInput(const Input& input, float deltaTime);
    void updateViewMat();
    void updateProjMat();
};