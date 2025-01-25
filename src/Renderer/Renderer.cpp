#include "Renderer.h"
#include "../Camera/Camera.h"
#include "../Light/Light.h"

#include <glad/glad.h>

std::vector<RenderObject> Renderer::m_renderQueue;
std::vector<std::shared_ptr<Light>> Renderer::m_lights;

void Renderer::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void Renderer::Update()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Retrieve the corresponding shader and draw each object in the render queue
	for (RenderObject const& renderObj : m_renderQueue) {
		Shader shader = Shader::Shaders.at(std::string(renderObj.shaderName));
		Transform transform = renderObj.object->GetTransform();
		std::shared_ptr<Camera> cam = Camera::GetActiveCamera();

		renderObj.object->GetModel()->Draw(shader, transform, cam, m_lights.at(0));
	}
}

void Renderer::AddRenderObject(RenderObject const& renderObj)
{
	m_renderQueue.push_back(renderObj);
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