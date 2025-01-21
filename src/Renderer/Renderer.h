#pragma once

#include "../Object/Object.h"

#include <vector>
#include <memory>

class Light;

class Renderer
{
public:
	Renderer() = delete;

	static void Initialize();
	static void Update();

	static void AddRenderObject(std::shared_ptr<Object> obj);
	static void AddLightObject(std::shared_ptr<Light> light);
	static void GetViewportSize(int& width, int& height);

private:
	static void DrawObject(std::shared_ptr<Object> object, std::shared_ptr<Camera> camera);

	static std::vector<std::shared_ptr<Object>> m_renderQueue;
	static std::vector<std::shared_ptr<Light>> m_lights;
};