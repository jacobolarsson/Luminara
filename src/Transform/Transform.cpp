#include "Transform.h"

mat4x4 Transform::GetModelMatrix() const
{
	mat4x4 scale = glm::scale(mat4x4(1.0f), m_scale);
	mat4x4 rotateX = glm::rotate(mat4x4(1.0f), glm::radians(m_rotation.x), { 1.0f, 0.0f, 0.0f });
	mat4x4 rotateY = glm::rotate(mat4x4(1.0f), glm::radians(m_rotation.y), { 0.0f, 1.0f, 0.0f });
	mat4x4 rotateZ = glm::rotate(mat4x4(1.0f), glm::radians(m_rotation.z), { 0.0f, 0.0f, 1.0f });
	mat4x4 translate = glm::translate(mat4x4(1.0f), m_position);

	return translate * rotateZ * rotateY * rotateX * scale;
}
