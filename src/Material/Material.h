#pragma once

#include "../Shader/Shader.h"
#include "../Transform/Transform.h"
#include "../Texture/Texture.h"

#include <memory>

class Material
{
public:
	Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture = nullptr)
		: m_shader(shader)
		, m_texture(texture)
	{}

	void Use() const;
	void UploadUniforms(Transform const& transform, std::shared_ptr<Camera> cam) const;
	void UploadTexture() const;
	void BindTexture() const;

private:
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Texture> m_texture;
};