#include "Camera.h"

Camera::Camera(int w, int h)
    : position{0, 0}, screenWidth(w), screenHeight(h) {}

void Camera::follow(const Entity& target) 
{
    position = target.position;
}