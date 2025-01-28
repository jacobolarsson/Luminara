#pragma once

#include "../Math/Math.h"

class Transform
{
public:
	Transform(vec3 pos = { 0.0f, 0.0f, 0.0f },
			  vec3 rot = { 0.0f, 0.0f, 0.0f },
			  vec3 sca = { 1.0f, 1.0f, 1.0f });

	mat4x4 GetModelMatrix() const;

	inline vec3 GetPosition() const { return m_position; }
	inline vec3 GetRotation() const { return m_rotation; }
	inline vec3 GetScale() const { return m_scale; }

	inline void SetPosition(vec3 position) { m_position = position; }
	inline void SetRotation(vec3 rotation) { m_rotation = rotation; }
	inline void SetScale (vec3 scale) { m_scale = scale; }

private:
	vec3 m_position;
	vec3 m_rotation;
	vec3 m_scale;
};