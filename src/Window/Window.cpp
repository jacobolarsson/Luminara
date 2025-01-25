#include "Window.h"
#include "../Time/Time.h"

#include <glad/glad.h>  
#include <GLFW/glfw3.h>

#include <iostream>

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
    glfwSwapInterval(1);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}
