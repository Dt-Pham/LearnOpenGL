#include "camera.hpp"

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float yaw, float pitch)
    : position(cameraPos),
      front(cameraFront),
      up(cameraUp),
      right(glm::vec3(0, 0, 0)), // this will get re-calculated 
      worldUp(cameraUp),
      yaw(yaw),
      pitch(pitch),
      movementSpeed(SPEED),
      mouseSensitivity(SENSITIVITY),
      zoom(ZOOM)
{
    updateCameraVector();
}

glm::mat4 Camera::viewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::Position() const
{
    return position;
}

glm::vec3 Camera::Front() const
{
    return front;
}

glm::vec3 Camera::Up() const
{
    return up;
}

glm::vec3 Camera::Right() const
{
    return right;
}

glm::vec3 Camera::WorldUp() const
{
    return worldUp;
}

float Camera::Yaw() const
{
    return yaw;
}

float Camera::Pitch() const
{
    return pitch;
}

float Camera::MovementSpeed() const
{
    return movementSpeed;
}

float Camera::MouseSesitivity() const
{
    return mouseSensitivity;
}

float Camera::Zoom() const
{
    return zoom;
}

void Camera::ProcessKeyboard(CameraMovement direction, float dt)
{
    float velocity = movementSpeed * dt;

    switch (direction)
    {
    case CameraMovement::FORWARD:
        position += front * velocity;
        break;
    
    case CameraMovement::BACKWARD:
        position -= front * velocity;
        break;
    
    case CameraMovement::LEFT:
        position -= right * velocity;
        break;
    
    case CameraMovement::RIGHT:
        position += right * velocity;
        break;
    }
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset)
{
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    updateCameraVector();
}

void Camera::ProcessMouseScroll(float yOffset)
{
    zoom -= yOffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}
void Camera::updateCameraVector()
{
    // calculate front vector
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    // recalculate right and up vector
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
