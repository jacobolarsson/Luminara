#include "Time.h"

#include <GLFW/glfw3.h>

float Time::m_deltaTime;
double Time::m_timeSinceStart;

void Time::Initialize()
{
	m_deltaTime = 0.0f;
	m_timeSinceStart = 0.0f;
}

void Time::Update()
{
	double currentTime = glfwGetTime();

	m_deltaTime = static_cast<float>(currentTime - m_timeSinceStart);
	m_timeSinceStart = currentTime;
}
