#include "Material.h"
#include "../Light/Light.h"

#include <glad/glad.h>
#include <iostream>

void Material::Use() const
{
	if (m_shader) {
		m_shader->Use();
	} else {
		std::cerr << "Material shader not set" << std::endl;
	}
}

void Material::UploadTexture() const
{
	if (m_texture) {
		m_texture->Upload();
	}
}

void Material::BindTexture() const
{
	if (m_texture) {
		m_texture->Bind();
	}
}

void Material::UploadShaderData(Transform const& transform,
								std::shared_ptr<Camera> cam,
								std::vector<std::shared_ptr<Light>> const& lights) const
{
	UploadShaderMtxData(transform, cam);
	UploadShaderLightData(lights, cam);
}

void Material::UploadShaderMtxData(Transform const& transform, std::shared_ptr<Camera> cam) const
{
	if (!m_shader) {
		std::cerr << "Material shader not set" << std::endl;
		return;
	}

	mat4x4 modelMtx = transform.ModelMatrix();
	mat4x4 modelToViewMtx = cam->ViewMatrix() * modelMtx;

	m_shader->UploadMat4x4("modelMtx", modelMtx);
	m_shader->UploadMat4x4("normalMtx", glm::transpose(glm::inverse(modelToViewMtx)));
	m_shader->UploadMat4x4("viewMtx", cam->ViewMatrix());
	m_shader->UploadMat4x4("projectionMtx", cam->ProjectionMatrix());
}

void Material::UploadShaderLightData(std::vector<std::shared_ptr<Light>> lights,
									 std::shared_ptr<Camera> cam) const
{
	if (!m_shader) {
		std::cerr << "Material shader not set" << std::endl;
		return;
	}

	switch (lights.at(0)->GetType())
	{
	case LightType::POINT:
		UploadShaderPointLightData(lights.at(0), cam);
		break;
	case LightType::DIR:
		UploadShaderDirLightData(lights.at(0), cam);
		break;
	case LightType::SPOT:
		UploadShaderSpotLightData(lights.at(0), cam);
		break;
	}
}

void Material::UploadShaderPointLightData(std::shared_ptr<Light> light,
										  std::shared_ptr<Camera> cam) const
{
	vec3 lightPos_world = light->GetTransform().GetPosition();

	m_shader->UploadVec3("lightPos_view", cam->ViewMatrix() * vec4(lightPos_world, 0.0f));
	m_shader->UploadVec3("lightColor", light->GetData().pointData.color);

	m_shader->UploadFloat("constAtt", light->GetData().pointData.constAtt);
	m_shader->UploadFloat("linAtt", light->GetData().pointData.linAtt);
	m_shader->UploadFloat("quadAtt", light->GetData().pointData.quadAtt);
}

void Material::UploadShaderDirLightData(std::shared_ptr<Light> light,
										std::shared_ptr<Camera> cam) const
{
}

void Material::UploadShaderSpotLightData(std::shared_ptr<Light> light,
										 std::shared_ptr<Camera> cam) const
{
}
