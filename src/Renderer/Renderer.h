#pragma once

#include "../Object/Object.h"

#include <vector>
#include <string>
#include <memory>

struct RenderObject
{
	std::shared_ptr<Object> object;
	std::string shaderName;
};

class Light;

class Renderer
{
public:
	Renderer() = delete;

	static void Initialize();
	static void Update();

	static void AddRenderObject(RenderObject const& renderObj);
	static void AddLightObject(std::shared_ptr<Light> light);
	static void GetViewportSize(int& width, int& height);
private:
	static std::vector<RenderObject> m_renderQueue;
	static std::vector<std::shared_ptr<Light>> m_lights;
};