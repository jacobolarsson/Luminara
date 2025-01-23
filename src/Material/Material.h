#pragma once

#include "../Shader/Shader.h"
#include "../Transform/Transform.h"
#include "../Texture/Texture.h"

#include <memory>
#include <vector>

class Light;

class Material
{
public:
	Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture = nullptr)
		: m_shader(shader)
		, m_texture(texture)
	{}

	void Use() const;
	void UploadTexture() const;
	void BindTexture() const;
	void UploadShaderData(Transform const& transform,
						  std::shared_ptr<Camera> cam,
						  std::vector<std::shared_ptr<Light>> const& lights) const;

private:
	void UploadShaderMtxData(Transform const& transform, std::shared_ptr<Camera> cam) const;
	void UploadShaderLightData(std::vector<std::shared_ptr<Light>> lights, std::shared_ptr<Camera> cam) const;

	void UploadShaderPointLightData(std::shared_ptr<Light> light, std::shared_ptr<Camera> cam) const;
	void UploadShaderDirLightData(std::shared_ptr<Light> light, std::shared_ptr<Camera> cam) const;
	void UploadShaderSpotLightData(std::shared_ptr<Light> light, std::shared_ptr<Camera> cam) const;

	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Texture> m_texture;
};