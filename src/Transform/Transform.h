#pragma once

#include <glm/vec3.hpp>

class Transform
{
public:

private:
	glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_scale = { 0.0f, 0.0f, 0.0f };
};