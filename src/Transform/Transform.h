#pragma once

#include "../Math/Math.h"

class Transform
{
public:
	mat4x4 GetModelMatrix() const;

private:
	vec3 m_position = { 0.0f, 0.0f, 0.0f };
	vec3 m_rotation = { 0.0f, 0.0f, 0.0f };
	vec3 m_scale = { 1.0f, 1.0f, 1.0f };
};