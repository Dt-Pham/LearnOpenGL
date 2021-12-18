#ifndef camera_hpp
#define camera_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// Default value
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(glm::vec3 cameraPos = glm::vec3(0, 0, 0), glm::vec3 cameraFront = glm::vec3(0, 0, -1), 
           glm::vec3 cameraUp = glm::vec3(0, 1, 0), float yaw = YAW, float pitch = PITCH);
    
    // getters
    glm::mat4 viewMatrix() const;

    glm::vec3 Position() const;
    glm::vec3 Front() const;
    glm::vec3 Up() const;
    glm::vec3 Right() const;
    glm::vec3 WorldUp() const;
    float Yaw() const;
    float Pitch() const;
    float MovementSpeed() const;
    float MouseSesitivity() const;
    float Zoom() const;

    // process input
    void ProcessKeyboard(CameraMovement direction, float dt);

    void ProcessMouseMovement(float xOffset, float yOffset);

    void ProcessMouseScroll(float yOffset);

private:
    // camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // euler angles
    float yaw;
    float pitch;
    // camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    void updateCameraVector();
};

#endif