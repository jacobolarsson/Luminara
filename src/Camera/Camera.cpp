#include "Camera.h"
#include "../Renderer/Renderer.h"

#include <glad/glad.h>

std::shared_ptr<Camera> Camera::m_activeCamera = nullptr;

Camera::Camera()
	: m_position(0.0f, 0.0f, 3.0f)
	, m_direction(0.0f, 0.0f, -1.0f)
	, m_rotation(0.0f, -90.0f, 0.0)
	, m_fov(60.0f)
	, m_near(0.01f)
	, m_far(1000.0f)
{}

mat4x4 Camera::ViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_direction, vec3(0.0f, 1.0f, 0.0f));
}

mat4x4 Camera::ProjectionMatrix()
{
	int width, height;
	Renderer::GetViewportSize(width, height);

	const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	return glm::perspective(glm::radians(m_fov), aspectRatio, m_near, m_far);
}

void Camera::Move(vec3 direction, float amount /*= 1.0f*/)
{
	m_position += glm::normalize(direction) * amount;
}

void Camera::SetRotation(vec3 rotation)
{
	// Restrain camera rotation to avoid flipping view
	if (rotation.x > 89.0f) {
		rotation.x = 89.0f;
	} else if (rotation.x < -89.0f) {
		rotation.x = -89.0f;
	}

	m_rotation = rotation;
}
