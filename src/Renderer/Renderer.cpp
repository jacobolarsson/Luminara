#include "Renderer.h"

#include <glad/glad.h>

std::vector<RenderObject> Renderer::m_renderQueue;

void Renderer::Initialize()
{

}

void Renderer::Update()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (RenderObject const& renderObj : m_renderQueue) {
		Draw(renderObj);
	}
}

void Renderer::AddRenderObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
{
	m_renderQueue.emplace_back(mesh, material);
}

void Renderer::Draw(RenderObject const& renderObj)
{
	renderObj.material->Use();
	renderObj.mesh->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
