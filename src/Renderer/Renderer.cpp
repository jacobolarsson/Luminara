#include "Renderer.h"
#include "../Camera/Camera.h"

#include <glad/glad.h>

std::vector<std::shared_ptr<Object>> Renderer::m_renderQueue;

void Renderer::Initialize()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer::Update()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::shared_ptr<Object> renderObj : m_renderQueue) {
		renderObj->GetMaterial()->UploadUniforms(renderObj->GetTransform(), Camera::GetActiveCamera());
		Draw(renderObj);
	}
}

void Renderer::AddRenderObject(std::shared_ptr<Object> obj)
{
	m_renderQueue.emplace_back(obj);
}

void Renderer::GetViewportSize(int& width, int& height)
{
	int viewportData[4];
	glGetIntegerv(GL_VIEWPORT, viewportData);

	width = viewportData[2];
	height = viewportData[3];
}

void Renderer::Draw(std::shared_ptr<Object> renderObj)
{
	renderObj->GetMaterial()->Use();
	renderObj->GetMaterial()->BindTexture();
	renderObj->GetMesh()->Bind();

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
