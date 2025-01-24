#include "Model.h"

#include "../Light/Light.h"

#include <glad/glad.h>

void Model::Load(const char* path)
{
}

void Model::Draw(Shader const& shader,
				 Transform const& transform,
				 std::shared_ptr<Camera> cam,
				 std::shared_ptr<Light> light) const
{
	UploadShaderData(shader, transform, cam, light);
	shader.Use();

	for (Mesh const& mesh : m_meshes) {
		mesh.Draw();
	}
}

void Model::UploadShaderData(Shader const& shader,
							 Transform const& transform,
							 std::shared_ptr<Camera> cam,
							 std::shared_ptr<Light> light) const
{
	UploadShaderMtxData(shader, transform, cam);
	// TODO: only pass light data if using a lit shader
	UploadShaderLightData(shader, cam, light);
}

void Model::UploadShaderMtxData(Shader const& shader,
								Transform const& transform,
								std::shared_ptr<Camera> cam) const
{
	mat4x4 modelMtx = transform.ModelMatrix();
	mat4x4 modelToViewMtx = cam->ViewMatrix() * modelMtx;

	shader.UploadMat4x4("modelMtx", modelMtx);
	shader.UploadMat4x4("normalMtx", glm::transpose(glm::inverse(modelToViewMtx)));
	shader.UploadMat4x4("viewMtx", cam->ViewMatrix());
	shader.UploadMat4x4("projectionMtx", cam->ProjectionMatrix());
}

void Model::UploadShaderLightData(Shader const& shader,
								  std::shared_ptr<Camera> cam,
								  std::shared_ptr<Light> light) const
{
	vec3 lightPos_world = light->GetTransform().GetPosition();

	shader.UploadVec3("lightPos_view", cam->ViewMatrix() * vec4(lightPos_world, 0.0f));
	shader.UploadVec3("lightColor", light->GetData().pointData.color);
		  
	shader.UploadFloat("constAtt", light->GetData().pointData.constAtt);
	shader.UploadFloat("linAtt", light->GetData().pointData.linAtt);
	shader.UploadFloat("quadAtt", light->GetData().pointData.quadAtt);
}
