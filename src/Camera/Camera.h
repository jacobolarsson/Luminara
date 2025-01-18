#pragma once

#include "../Math/Math.h"

#include <memory>

class Camera
{
public:
	Camera();

	mat4x4 ViewMatrix();
	mat4x4 ProjectionMatrix();
	void Move(vec3 direction, float amount = 1.0f);

	inline static void SetActiveCamera(std::shared_ptr<Camera> cam) { m_activeCamera = cam; }
	inline static std::shared_ptr<Camera> GetActiveCamera() { return m_activeCamera; }

	inline vec3 const& GetPosition() const { return m_position; }
	inline vec3 const& GetDirection() const { return glm::normalize(m_direction); }
	inline vec3 const& GetRotation() const { return m_rotation; }

	inline void SetDirection(vec3 direction) { m_direction = glm::normalize(direction); }
	void SetRotation(vec3 rotation);

private:
	static std::shared_ptr<Camera> m_activeCamera;

	vec3 m_position;
	vec3 m_direction;
	vec3 m_rotation;
	float m_fov;
	float m_near;
	float m_far;
};