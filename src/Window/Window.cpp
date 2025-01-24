#include "Window.h"
#include "../Time/Time.h"

#include <glad/glad.h>  
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include <thread>

GLFWwindow* Window::m_window;

void OnWindowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::Initialize()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window and set as current context
    m_window = glfwCreateWindow(1280, 720, "Luminara", NULL, NULL);
    if (m_window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, 1280, 720);
    glfwSetFramebufferSizeCallback(m_window, OnWindowResize);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    // Limit framerate to 144 fps
    size_t frameDurationMs = static_cast<size_t>(Time::GetDeltaTime() * 1000.0f);
    size_t targetFrameDurationMs = static_cast<size_t>(1000.0f / 144.0f);

    if (frameDurationMs < targetFrameDurationMs) {
        size_t diff = targetFrameDurationMs - frameDurationMs;
        std::this_thread::sleep_for(std::chrono::milliseconds(diff));
    }

    glfwSwapBuffers(m_window);
}
