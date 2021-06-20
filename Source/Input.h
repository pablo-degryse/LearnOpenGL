#pragma once

struct Input
{
    bool moveForward;
    bool moveBackward;
    bool moveLeft;
    bool moveRight;
    float lastMouseX;
    float lastMouseY;
    float mouseMoveX;
    float mouseMoveY;
    bool mousePosInitialized;
    float currentScroll;
    float lastScroll;
    float scrollDiff;
};