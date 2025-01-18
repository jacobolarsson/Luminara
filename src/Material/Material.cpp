#include "Material.h"

#include <iostream>

void Material::Use() const
{
	if (m_shader) {
		m_shader->Use();
	} else {
		std::cerr << "Material shader not set" << std::endl;
	}
}

void Material::UploadUniforms(Transform const& transform, std::shared_ptr<Camera> cam)
{
	if (!m_shader) {
		std::cerr << "Material shader not set" << std::endl;
		return;
	}

	m_shader->UploadMat4x4("model", transform.GetModelMatrix());
	m_shader->UploadMat4x4("view", cam->ViewMatrix());
	m_shader->UploadMat4x4("projection", cam->ProjectionMatrix());
}
