#pragma once

#include "../Shader/Shader.h"

#include <memory>

class Material
{
public:
	Material(std::shared_ptr<Shader> shader) : m_shader(shader) {}

	void Use() const;
private:
	std::shared_ptr<Shader> m_shader;
};