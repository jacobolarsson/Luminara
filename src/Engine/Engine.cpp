#include "Engine.h"
#include "../Window/Window.h"
#include "../World/World.h"
#include "../Input/Input.h"
#include "../Renderer/Renderer.h"

#include <glad/glad.h>  
#include <GLFW/glfw3.h>

void Engine::Initialize()
{
	Window::Initialize();
    World::Initialize();
}

void Engine::Run()
{
    while (!Window::ShouldClose())
    {
        Input::Update();
        Renderer::Update();
        Window::SwapBuffers();
    }

    glfwTerminate();
}
