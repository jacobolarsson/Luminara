#pragma once

#include "../Mesh/Mesh.h"
#include "../Material/Material.h"
#include "../Object/Object.h"

#include <vector>
#include <memory>

class Renderer
{
public:
	Renderer() = delete;

	static void Initialize();
	static void Update();

	static void AddRenderObject(std::shared_ptr<Object> obj);
	static void GetViewportSize(int& width, int& height);

private:
	static void Draw(std::shared_ptr<Object> renderObj);

	static std::vector<std::shared_ptr<Object>> m_renderQueue;
};