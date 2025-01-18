#pragma once

#include "../Shader/Shader.h"
#include "../Transform/Transform.h"

#include <memory>

class Material
{
public:
	Material(std::shared_ptr<Shader> shader) : m_shader(shader) {}

	void Use() const;
	void UploadUniforms(Transform const& transform, std::shared_ptr<Camera> cam);

private:
	std::shared_ptr<Shader> m_shader;
};