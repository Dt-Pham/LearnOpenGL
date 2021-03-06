#include "root_dir.h"
#include "stb_image.h"
#include "shaders/shader.hpp"
#include "camera/camera.hpp"
#include "model_loading/model.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xOffset, double yOffset); 
void processInput(GLFWwindow* window);

// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

// camera
Camera mainCamera(glm::vec3(0, 0, 3));
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;
bool firstMouse = true;
bool mousePressed = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // Initialize the library
    if(!glfwInit())
        return -1;

    // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Mathe the window's context current
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Initialize the OpenGL API with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    //Shader lightingShader(ROOT_DIR"src/Shaders/lighting.vs", ROOT_DIR"src/Shaders/lighting.fs");
    //Shader lightSourceShader(ROOT_DIR"src/Shaders/light_source.vs", ROOT_DIR"src/Shaders/light_source.fs");
    Shader basicShader(ROOT_DIR"src/Shaders/basic.vs", ROOT_DIR"src/Shaders/basic.fs");

    Model backpack(ROOT_DIR"resources/backpack/backpack.obj");

    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        processInput(window);
        
        // Render here!
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = mainCamera.viewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(mainCamera.Zoom()), 
                                                static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 
                                                0.1f, 100.0f);

        basicShader.use();
        basicShader.setMat4("projection", projection);
        basicShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        basicShader.setMat4("model", model);
        backpack.Draw(basicShader);
        
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina displays
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    // Wireframe mode
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
    
    // Normal mode
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Camera movement
    if (glfwGetKey(window, GLFW_KEY_W))
        mainCamera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S))
        mainCamera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A))
        mainCamera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D))
        mainCamera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
    if (!mousePressed)
        return;

    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos; // reversed

    lastX = xPos;
    lastY = yPos;

    mainCamera.ProcessMouseMovement(xOffset, yOffset);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        mousePressed = true;
        firstMouse = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        mousePressed = false;
}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    mainCamera.ProcessMouseScroll(yOffset);
}
