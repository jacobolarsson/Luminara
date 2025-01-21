#include "Renderer.h"
#include "../Camera/Camera.h"
#include "../Light/Light.h"

#include <glad/glad.h>

std::vector<std::shared_ptr<Object>> Renderer::m_renderQueue;
std::vector<std::shared_ptr<Light>> Renderer::m_lights;

void Renderer::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
}

void Renderer::Update()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::shared_ptr<Object> renderObj : m_renderQueue) {
		DrawObject(renderObj, Camera::GetActiveCamera());
	}
}

void Renderer::AddRenderObject(std::shared_ptr<Object> obj)
{
	m_renderQueue.push_back(obj);
}

void Renderer::AddLightObject(std::shared_ptr<Light> light)
{
	m_lights.push_back(light);
}

void Renderer::GetViewportSize(int& width, int& height)
{
	int viewportData[4];
	glGetIntegerv(GL_VIEWPORT, viewportData);

	width = viewportData[2];
	height = viewportData[3];
}

void Renderer::DrawObject(std::shared_ptr<Object> object, std::shared_ptr<Camera> camera)
{
	object->GetMaterial()->UploadShaderLightData(m_lights[0]);
	object->GetMaterial()->UploadShaderMtxData(object->GetTransform(), camera);

	object->GetMaterial()->Use();
	object->GetMaterial()->BindTexture();
	object->GetMesh()->Bind();

	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawElements(GL_TRIANGLES, object->GetMesh()->GetIdxCount(), GL_UNSIGNED_INT, 0);
}