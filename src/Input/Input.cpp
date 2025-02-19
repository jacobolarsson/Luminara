#include "Input.h"
#include "../Window/Window.h"	
#include "../Camera/Camera.h"	
#include "../Time/Time.h"
#include "../Renderer/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

MouseData Input::m_mouseData = { true, 0.0f, 0.0f };

void OnMouseMove(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    MouseData mouseData = Input::GetMouseData();
    if (mouseData.firstMouse)
    {
        mouseData.lastX = xpos;
        mouseData.lastY = ypos;
        mouseData.firstMouse = false;
    }

    float xoffset = xpos - mouseData.lastX;
    float yoffset = mouseData.lastY - ypos; // reversed because y coordinates go from bottom to top
    mouseData.lastX = xpos;
    mouseData.lastY = ypos;

    Input::SetMouseData(mouseData);

    // Only move camera with mouse if holding right click
    if (glfwGetMouseButton(Window::GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS) {
        glfwSetInputMode(Window::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return;
    }

    glfwSetInputMode(Window::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    std::shared_ptr<Camera> activeCam = Camera::GetActiveCamera();
    // Update pitch and yaw
    vec3 newRotation = activeCam->GetRotation() + vec3(yoffset, xoffset, 0.0f);
    activeCam->SetRotation(newRotation); 

    float pitch = activeCam->GetRotation().x;
    float yaw = activeCam->GetRotation().y;

    // Compute new camera direction based on pitch and yaw
    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    activeCam->SetDirection(dir);
}

void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Toggle wireframe mode
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        RenderConfig newConfig = { !Renderer::GetConfig().wireframeMode };
        Renderer::SetConfig(newConfig);
    }
}

void Input::Initialize()
{
    glfwSetCursorPosCallback(Window::GetWindow(), OnMouseMove);
    glfwSetKeyCallback(Window::GetWindow(), OnKeyPressed);
}

void Input::Update()
{
	if (glfwGetKey(Window::GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(Window::GetWindow(), true);
	}

    UpdateActiveCamera();
	glfwPollEvents();
}

void Input::UpdateActiveCamera()
{
	vec3 camDir = Camera::GetActiveCamera()->GetDirection();
	vec3 camRight = glm::normalize(glm::cross(camDir, { 0.0f, 1.0f, 0.0f }));
	float camSpeed = 3.0f * Time::GetDeltaTime();

	if (glfwGetKey(Window::GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		Camera::GetActiveCamera()->Move(camDir, camSpeed);
	}
	if (glfwGetKey(Window::GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		Camera::GetActiveCamera()->Move(-camDir, camSpeed);
	}
	if (glfwGetKey(Window::GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		Camera::GetActiveCamera()->Move(-camRight, camSpeed);
	}
	if (glfwGetKey(Window::GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		Camera::GetActiveCamera()->Move(camRight, camSpeed);
	}
	if (glfwGetKey(Window::GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		Camera::GetActiveCamera()->Move({0.0f, 1.0f, 0.0f}, camSpeed);
	}
	if (glfwGetKey(Window::GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		Camera::GetActiveCamera()->Move({ 0.0f, -1.0f, 0.0f }, camSpeed);
	}
}
