#include "World.h"
#include "../Renderer/Renderer.h"

std::unordered_set<std::shared_ptr<Object>> World::m_objects;

void World::Initialize()
{
	Transform trans;
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->Load();

	std::shared_ptr<Shader> shader = std::make_shared<Shader>("data/shaders/standard.vert",
															  "data/shaders/standard.frag");

	std::shared_ptr<Material> mat = std::make_shared<Material>(shader);
	std::shared_ptr<Object> obj = std::make_shared<Object>(trans, mesh, mat);

	AddObject(obj);
}

void World::AddObject(std::shared_ptr<Object> obj)
{
	// If object is already present
	if (m_objects.find(obj) != m_objects.end()) {
		return;
	}

	m_objects.insert(obj);

	Renderer::AddRenderObject(obj->GetMesh(), obj->GetMaterial());
}

void World::RemoveObject(std::shared_ptr<Object> obj)
{
	// If object not is present
	if (m_objects.find(obj) == m_objects.end()) {
		return;
	}

	m_objects.erase(obj);
}
