#include "Input.h"
#include "../Window/Window.h"	

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Input::Update()
{
	if (glfwGetKey(Window::GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(Window::GetWindow(), true);
	}

	glfwPollEvents();
}
