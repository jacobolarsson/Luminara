#pragma once

#include "../Mesh/Mesh.h"
#include "../Material/Material.h"

#include <vector>
#include <memory>

struct RenderObject
{
	RenderObject(std::shared_ptr<Mesh> mes, std::shared_ptr<Material> mat)
		: mesh(mes), material(mat)
	{}

	std::shared_ptr<Mesh> mesh = nullptr;
	std::shared_ptr<Material> material = nullptr;
};

class Renderer
{
public:
	Renderer() = delete;

	static void Initialize();
	static void Update();

	static void AddRenderObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

private:
	static void Draw(RenderObject const& renderObj);

	static std::vector<RenderObject> m_renderQueue;
};